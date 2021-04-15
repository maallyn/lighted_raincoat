#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <wiringPi.h>

#define DATA1 2
#define CLOCK1 3
#define LED_START 0xfe

#define TOTAL_LEDS 2000
#define TOTAL_STRIPS 100
#define TOTAL_LOG_STRINGS 200
#define TOTAL_PHY_STRINGS 100
#define NAME_LENGTH 20
#define SIZE_INPUT_STRING 100

/* Enumeration For Reading Garment YAML File */

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
  char name[NAME_LENGTH];
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
  char name[NAME_LENGTH];
  int string_length;
  strip_type *physical_strip;
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
static logical_string_type *logical_strings = NULL;
static int number_logical_strings = 0;
static led_type *leds = NULL;
static int number_leds = 0;

void setup_memory()
  {
  if ((strips = (strip_type *)calloc(TOTAL_STRIPS * sizeof(strip_type), 1)) == NULL)
    {
    printf("cannot allocate strips\n");
    exit(0);
    }
  if ((physical_strings = 
    (physical_string_type *)calloc(TOTAL_PHY_STRINGS * 
    sizeof(physical_string_type), 1)) == NULL)
    {
    printf("cannot allocate physical strings\n");
    free(strips);
    strips = NULL;
    }
  if ((logical_strings = 
    (logical_string_type *)calloc(TOTAL_LOG_STRINGS * 
    sizeof(logical_string_type), 1)) == NULL)
    {
    printf("cannot allocate logical strings\n");
    free(strips);
    strips = NULL;
    free(physical_strings);
    physical_strings = NULL;
    }
  if ((leds = (led_type *)calloc(TOTAL_LEDS * sizeof(led_type), 1)) == NULL)
    {
    printf("cannot allocate leds\n");
    free(strips);
    strips = NULL;
    free(physical_strings);
    physical_strings = NULL;
    free(logical_strings);
    logical_strings = NULL;
    exit(0);
    }
  }

void setup_physical_strips()
  {
  strip_type *current_strip = NULL;
  int strip_count = 0;

  if (strips == NULL) return;

  /* GPIO Initialization */
  wiringPiSetupGpio();

  /* Set up the gpio pins for each strip */
  current_strip = strips;
  for (strip_count = 0; strip_count <= number_strips; strip_count += 1)
    {
    pinMode(current_strip->data_cpio, OUTPUT);
    pullUpDnControl(current_strip->data_cpio, PUD_UP);
    pinMode(current_strip->clock_cpio, OUTPUT);
    pullUpDnControl(current_strip->clock_cpio, PUD_UP);

    /* Remember that we set these high, but they
       be low at the 5 volt output, which is inverted */
    digitalWrite(current_strip->data_cpio, HIGH);
    digitalWrite(current_strip->clock_cpio, HIGH);
    }
  }

void send_byte(unsigned char inval, strip_type *send_strip)
  {
  int ct1;
  unsigned char workval;
  workval = inval;
  if (send_strip == NULL) return;

  for (ct1 = 0; ct1 < 8; ct1 += 1)
    {
    /* push clock to low (this does not matter when) */
    digitalWrite(send_strip->clock_cpio, HIGH);
    /* set data to whichever, based on the bit */
    if ((workval & 0x80) == 0)
      {
      digitalWrite(send_strip->data_cpio, HIGH);
      }
    else
      {
      digitalWrite(send_strip->data_cpio, LOW);
      }
    /* wait 5 us and then set clock to high */
    /* low to high transition is what clocks data in */
    delayMicroseconds(5);
    digitalWrite(send_strip->clock_cpio, LOW);
    delayMicroseconds(5);
    /* wait 5 us and then shift to next bit */
    workval = workval << 1;
    }
  }

/* The start for each stip of LED is four zeros */
void send_start(strip_type *start_strip)
  {
  if (start_strip == NULL) return;
  send_byte((unsigned char)0, start_strip);
  send_byte((unsigned char)0, start_strip);
  send_byte((unsigned char)0, start_strip);
  send_byte((unsigned char)0, start_strip);
  }

/* Send the three colors and control byte for one LED */
void send_led(led_type *led, strip_type *color_strip)
  {
  if (color_strip == NULL) return;
  send_byte((unsigned char)LED_START, color_strip);
  send_byte(led->blue_byte, color_strip);
  send_byte(led->green_byte, color_strip);
  send_byte(led->red_byte, color_strip);
  }

/* Send the end of the strip */
void send_end(strip_type *end_strip)
  {
  if (end_strip == NULL) return;
  send_byte((unsigned char)0xff, end_strip);
  send_byte((unsigned char)0xff, end_strip);
  send_byte((unsigned char)0xff, end_strip);
  send_byte((unsigned char)0xff, end_strip);
  send_byte((unsigned char)0xff, end_strip);
  send_byte((unsigned char)0xff, end_strip);
  send_byte((unsigned char)0xff, end_strip);
  send_byte((unsigned char)0xff, end_strip);
  send_byte((unsigned char)0xff, end_strip);
  send_byte((unsigned char)0xff, end_strip);
  send_byte((unsigned char)0xff, end_strip);
  send_byte((unsigned char)0xff, end_strip);
  }

void send_physical_string(physical_string_type *physical_string)
  {
  int led_count;

  send_start(physical_string->physical_strip);
  for (led_count = 0; led_count < physical_string->string_length; led_count += 1)
    {
    send_led(physical_string->string_leds + led_count, physical_string->physical_strip);
    }
  send_end(physical_string->physical_strip);
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
  
/* Opens and parses the config file */
int openconfig(char *filename)
  {
  FILE *fpconfig = NULL;
  char instg[SIZE_INPUT_STRING];
  char *cpres;
  char *substring;
  
  int len;
  int res;
  int count_physical;
  int count_leds;
  int count_logical;
  int count_strips;
  int count_leds_in_logical;
  int count_leds_in_physical;
  int count_logical_in_physical;
  
  count_physical = 0;
  count_leds = 0;
  count_logical = 0;
  count_strips = 0;

  if ((fpconfig = fopen(filename, "r")) == NULL)
    {
    printf("cannot open config file\n");
    return -1;
    }
    
  while ((cpres = fgets(instg, SIZE_INPUT_STRING, fpconfig)) != NULL)
    {
    len = strlen(instg);
    if (instg[len - 1] == '\n') instg[len - 1] = 0;
    printf("string is %s \n", instg);

    substring = strtok(instg, " ");
    printf("first substring is %s\n", substring);
    substring = strtok(NULL," ");
    printf("second substring is %s\n", substring);
    }

  return 0;
  }

   
int main(int argc, char **argv)
  {
  int res = 0;

  if (argc < 2)
    {
    printf("need config file name as argument\n");
    exit(1);
    }

  setup_memory();
  res = openconfig(*(argv + 1));
  if (res != 0)
    {
    printf("could not open/process config file\n");
    exit(1);
    }

  }
