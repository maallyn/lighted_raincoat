#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <wiringPi.h>
#include <yaml.h>

#define DATA1 2
#define CLOCK1 3
#define LED_START 0xfe

/* Physical strips of LEDs */
struct strip_struct
  {
  int data_cpio;
  int clock_cpio;
  };

typedef struct strip_struct strip_type;

/* Data for each LED */
struct led_struct
  {
  unsigned char blue_byte;
  unsigned char green_byte;
  unsigned char red_byte;
  };

typedef struct led_struct led_type;

/* Logical strings; there can be more than one
   for each physical string; for example, one
   physical strip can include back, neck, and arm
   of the garment */
struct logical_string_struct
  {
  int direction;
  int length;
  int start_location;
  led_type *string_leds;
  };

typedef struct logical_string_struct logical_string_type;

/* This is the definition of the physical string of LEDs
   This is what is output to an LED strip. We do not associate
   the physical string to a strip as there can be more than one
   physical string for each strip, which allows for pipelining
   between preparation and display of LED strings */
struct physical_string_struct
  {
  int string_length;
  int strip;
  led_type *string_leds;
  int nbr_log_strings;
  logical_string_type *log_strings_live;
  logical_string_type *log_strings_standby;
  };

typedef struct physical_string_struct physical_string_type;

/* Global data; all strips and LED strings for entire garment */
static strip_type *strips = NULL;
static int number_strips = 0;
static physical_string_type *physical_strings = NULL;
static int number_physical_strings = 0;

void setup()
  {
  /* Set up the gpio pins */
  wiringPiSetupGpio();
  pinMode(DATA1, OUTPUT);
  pullUpDnControl(DATA1, PUD_UP);
  pinMode(CLOCK1, OUTPUT);
  pullUpDnControl(CLOCK1, PUD_UP);

  /* Remember that we set these his, but they
     be low at the 5 volt output, which is inverted */
  digitalWrite(DATA1, HIGH);
  digitalWrite(CLOCK1, HIGH);
  }

void send_byte(unsigned char inval, int strip)
  {
  int ct1;
  unsigned char workval;
  workval = inval;
  if (strips == NULL) return;
  if (strip >= number_strips) return;

  for (ct1 = 0; ct1 < 8; ct1 += 1)
    {
    /* push clock to low (this does not matter when) */
    digitalWrite((strips + strip)->clock_cpio, HIGH);
    /* set data to whichever, based on the bit */
    if ((workval & 0x80) == 0)
      {
      digitalWrite((strips + strip)->data_cpio, HIGH);
      }
    else
      {
      digitalWrite((strips + strip)->data_cpio, LOW);
      }
    /* wait 5 us and then set clock to high */
    /* low to high transition is what clocks data in */
    delayMicroseconds(5);
    digitalWrite((strips + strip)->clock_cpio, LOW);
    delayMicroseconds(5);
    /* wait 5 us and then shift to next bit */
    workval = workval << 1;
    }
  }

/* The start for each stip of LED is four zeros */
void send_start(int strip)
  {
  send_byte((unsigned char)0, strip);
  send_byte((unsigned char)0, strip);
  send_byte((unsigned char)0, strip);
  send_byte((unsigned char)0, strip);
  }

/* Send the three colors and control byte for one LED */
void send_led(led_type *led, int strip)
  {
  send_byte((unsigned char)LED_START, strip);
  send_byte(led->blue_byte, strip);
  send_byte(led->green_byte, strip);
  send_byte(led->red_byte, strip);
  }

/* Send the end of the strip */
void send_end(int strip)
  {
  send_byte((unsigned char)0xff, strip);
  send_byte((unsigned char)0xff, strip);
  send_byte((unsigned char)0xff, strip);
  send_byte((unsigned char)0xff, strip);
  send_byte((unsigned char)0xff, strip);
  send_byte((unsigned char)0xff, strip);
  send_byte((unsigned char)0xff, strip);
  send_byte((unsigned char)0xff, strip);
  send_byte((unsigned char)0xff, strip);
  send_byte((unsigned char)0xff, strip);
  send_byte((unsigned char)0xff, strip);
  send_byte((unsigned char)0xff, strip);
  }

void send_physical_string(physical_string_type *physical_string)
  {
  int led_count;

  send_start(physical_string->strip);
  for (led_count = 0; led_count < physical_string->string_length; led_count += 1)
    {
    send_led(physical_string->string_leds + led_count, physical_string->strip);
    }
  send_end(physical_string->strip);
  }

/* Copies set of logical strings to the physical string to be sent
   to LEDs. Note that because of wiring, some logical strings would
   be reverse in appearance. Think for example collar top would be
   wired left to right, but collar bottom would be wired right to left
   in order to save on lengthy inter-string wiring which can be a source
   of trouble. The can be very important for skirts where you have one
   string going down the skirt to the hem and the next string going up
   the skirt to the belt. */
void load_physical_string(physical_string_type *physical_string)
  {
  logical_string_type *current_live_string = NULL;
  logical_string_type *working_logical_string = NULL;
  led_type *source_led = NULL;
  led_type *destination_led = NULL;
  int logical_string_ctr = 0;
  int led_ctr = 0;
  int true_offset = 0;
  int direction = 0;
  int logical_length = 0;

  if (physical_string == NULL) return;
  if (physical_string->log_strings_live == NULL) return;

  current_live_string = physical_string->log_strings_live;
  destination_led = physical_string->string_leds;

  for (logical_string_ctr = 0; logical_string_ctr < physical_string->nbr_log_strings;
       logical_string_ctr += 1)
    {
    working_logical_string = current_live_string + logical_string_ctr;
    source_led = working_logical_string->string_leds;
    destination_led = physical_string->string_leds + working_logical_string->start_location;
    direction = working_logical_string->direction;
    logical_length = working_logical_string->length;
    for (led_ctr = 0; led_ctr < logical_length; led_ctr += 1)
      {
      if (direction == 0) true_offset = led_ctr;
      else true_offset = logical_length - 1 - led_ctr;
      destination_led->blue_byte = (source_led + true_offset)->blue_byte;
      destination_led->green_byte = (source_led + true_offset)->green_byte;
      destination_led->red_byte = (source_led + true_offset)->red_byte;
      destination_led += 1;
      }
    }
  }
  
/* Opens and parses the yaml file */
int openyaml(char *filename)
  {
  FILE *fh = NULL;
  yaml_parser_t parser;
  yaml_token_t token;

  if(!yaml_parser_initialize(&parser))
    {
    printf("Cannot initialize parse\n");
    return 1;
    }
  if ((fh = fopen(filename, "r")) == NULL)
    {
    printf("cannot open yaml file %s\n", filename);
    return 1;
    }
  yaml_parser_set_input_file(&parser, fh);

  do
    {
    yaml_parser_scan(&parser, &token);
    switch(token.type)
      {
      case YAML_STREAM_START_TOKEN:
        printf("\n\nSTREAM START\n");
        break;
      case YAML_STREAM_END_TOKEN:
        printf("\n\nSTREAM END\n");
        break;
      case YAML_KEY_TOKEN:
        printf("\n\n(Key token)\n");
        break;
      case YAML_VALUE_TOKEN:
        printf("\n\n(Value token)\n");
        break;
      case YAML_BLOCK_SEQUENCE_START_TOKEN: 
        printf("\n\nStart Block Sequence\n");
        break;
      case YAML_BLOCK_ENTRY_TOKEN: 
        printf("\n\nStart Block entry\n");
        break;
      case YAML_BLOCK_END_TOKEN: 
        printf("\n\nEnd Block\n");
        break;
      case YAML_BLOCK_MAPPING_START_TOKEN:
        printf("\n\nBlock Mapping\n");
        break;
      case YAML_SCALAR_TOKEN:
        printf("Scaler %s \n", token.data.scalar.value);
        break;
      default:
        printf("\n\nGot token type %d\n", token.type);
      }
    if (token.type != YAML_STREAM_END_TOKEN)
      yaml_token_delete(&token);
    } while (token.type != YAML_STREAM_END_TOKEN);

  yaml_token_delete(&token);
  yaml_parser_delete(&parser);
  fclose(fh);
  return 0;
  }

   
int main(int argc, char **argv)
  {
  int strip = 0;
  int res = 0;
  
  if (argc < 2)
    {
    printf("need yaml file name as argument\n");
    exit(1);
    }

  setup();

  res = openyaml(*(argv + 1));
  if (res != 0)
    {
    printf("could not open/process yaml file\n");
    exit(1);
    }

  }
