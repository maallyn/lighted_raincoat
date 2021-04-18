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

#define NAME_LENGTH 30
#define SIZE_INPUT_STRING 100

/* Enumerations */
enum animation_enum_type {stable, crawl};
enum state_we_are_in_type {physical, logical};

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
  enum animation_enum_type animation;
  led_type initial_color[5]; /* For start colors */
  int border_size; /* borders between color crawls */
  int direction;
  int length;
  int start_location;
  led_type *string_leds;
  };

typedef struct logical_string_struct logical_string_type;

/* This is the definition of the physical string of LEDs
   This is what is output to an LED strip. */
struct physical_string_struct
  {
  char name[NAME_LENGTH];
  int gpio_clock_pin;
  int gpio_data_pin;
  int string_length;
  led_type *string_leds;
  int nbr_log_strings;
  logical_string_type *log_string;
  };

typedef struct physical_string_struct physical_string_type;

/* Global data; all and LED strings for entire garment */
static physical_string_type *physical_strings = NULL;
static int number_physical_strings = 0;
static logical_string_type *logical_strings = NULL;
static int number_logical_strings = 0;
static led_type *leds = NULL;
static int number_leds = 0;
static led_type *physical_string_leds = NULL;
static int number_physical_string_leds = 0;

void force_lower(char *this_stg, int this_size)
  {
  int ctr;
  for (ctr = 0; ctr < this_size; ctr += 1)
    {
    if ((this_stg[ctr] >= 65) && (this_stg[ctr] <= 90))
      {
      this_stg[ctr] = this_stg[ctr] + 32;
      }
    }
  }

void setup_memory()
  {
  if ((physical_strings = 
    (physical_string_type *)calloc(number_physical_strings * 
    sizeof(physical_string_type), 1)) == NULL)
    {
    printf("cannot allocate physical strings\n");
    exit(0);
    }
  if ((logical_strings = 
    (logical_string_type *)calloc(number_logical_strings * 
    sizeof(logical_string_type), 1)) == NULL)
    {
    printf("cannot allocate logical strings\n");
    free(physical_strings);
    physical_strings = NULL;
    exit(0);
    }
  if ((leds = (led_type *)calloc(number_leds * sizeof(led_type), 1)) == NULL)
    {
    printf("cannot allocate leds\n");
    free(physical_strings);
    physical_strings = NULL;
    free(logical_strings);
    logical_strings = NULL;
    exit(0);
    }
  if ((physical_string_leds = (led_type *)calloc(number_physical_string_leds *
      sizeof(led_type), 1)) == NULL)
    {
    printf("cannot allocate physical_string_leds\n");
    free(physical_strings);
    physical_strings = NULL;
    free(logical_strings);
    logical_strings = NULL;
    free(leds);
    exit(0);
    }
  }

void setup_physical_string_gpio_pins()
  {
  physical_string_type *current_physical;
  int physical_count = 0;

  if (physical_strings == NULL) return;

  /* GPIO Initialization */
  wiringPiSetupGpio();

  /* Set up the gpio pins for each physical string */
  current_physical = physical_strings;
  for (physical_count = 0; physical_count <= number_physical_strings;
      physical_count += 1)
    {
    pinMode(current_physical->gpio_data_pin, OUTPUT);
    pullUpDnControl(current_physical->gpio_data_pin, PUD_UP);
    pinMode(current_physical->gpio_clock_pin, OUTPUT);
    pullUpDnControl(current_physical->gpio_clock_pin, PUD_UP);

    /* Remember that we set these high, but they
       be low at the 5 volt output, which is inverted */
    digitalWrite(current_physical->gpio_data_pin, HIGH);
    digitalWrite(current_physical->gpio_clock_pin, HIGH);
    }
  }

void send_byte(unsigned char inval, physical_string_type *send_string)
  {
  int ct1;
  unsigned char workval;
  workval = inval;
  if (send_string == NULL) return;

  for (ct1 = 0; ct1 < 8; ct1 += 1)
    {
    /* push clock to low (this does not matter when) */
    digitalWrite(send_string->gpio_clock_pin, HIGH);
    /* set data to whichever, based on the bit */
    if ((workval & 0x80) == 0)
      {
      digitalWrite(send_string->gpio_data_pin, HIGH);
      }
    else
      {
      digitalWrite(send_string->gpio_data_pin, LOW);
      }
    /* wait 5 us and then set clock to high */
    /* low to high transition is what clocks data in */
    delayMicroseconds(5);
    digitalWrite(send_string->gpio_clock_pin, LOW);
    delayMicroseconds(5);
    /* wait 5 us and then shift to next bit */
    workval = workval << 1;
    }
  }

/* The start for each stip of LED is four zeros */
void send_start(physical_string_type *start_string)
  {
  if (start_string == NULL) return;
  send_byte((unsigned char)0, start_string);
  send_byte((unsigned char)0, start_string);
  send_byte((unsigned char)0, start_string);
  send_byte((unsigned char)0, start_string);
  }

/* Send the three colors and control byte for one LED */
void send_led(led_type *led, physical_string_type *color_string)
  {
  if (color_string == NULL) return;
  send_byte((unsigned char)LED_START, color_string);
  send_byte(led->blue_byte, color_string);
  send_byte(led->green_byte, color_string);
  send_byte(led->red_byte, color_string);
  }

/* Send the end of the string */
void send_end(physical_string_type *end_string)
  {
  if (end_string == NULL) return;
  send_byte((unsigned char)0xff, end_string);
  send_byte((unsigned char)0xff, end_string);
  send_byte((unsigned char)0xff, end_string);
  send_byte((unsigned char)0xff, end_string);
  send_byte((unsigned char)0xff, end_string);
  send_byte((unsigned char)0xff, end_string);
  send_byte((unsigned char)0xff, end_string);
  send_byte((unsigned char)0xff, end_string);
  send_byte((unsigned char)0xff, end_string);
  send_byte((unsigned char)0xff, end_string);
  send_byte((unsigned char)0xff, end_string);
  send_byte((unsigned char)0xff, end_string);
  }

void send_physical_string(physical_string_type *physical_string)
  {
  int led_count;

  send_start(physical_string);
  for (led_count = 0; led_count < physical_string->string_length; led_count += 1)
    {
    send_led(physical_string->string_leds + led_count, physical_string);
    }
  send_end(physical_string);
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
  if (physical_string->log_string == NULL) return;

  current_live_string = physical_string->log_string;
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
  
/* Opens and parses the config file to size up
   what storage is needed for the leds, physical
   and logical strings */
int count_leds_and_strings(char *filename)
  {
  FILE *fpconfig = NULL;
  char instg[SIZE_INPUT_STRING];
  char *cpres;
  char *substring;
  
  int len;
  int count_physical;
  int count_led;
  int count_physical_leds;
  int count_logical;
  int int_value;

  char the_tag[30];
  char the_value[30];
  
  count_physical = 0;
  count_led = 0;
  count_physical_leds = 0;

  count_logical = 0;

  if ((fpconfig = fopen(filename, "r")) == NULL)
    {
    printf("cannot open config file\n");
    return -1;
    }
    
  while ((cpres = fgets(instg, SIZE_INPUT_STRING, fpconfig)) != NULL)
    {
    force_lower(instg, SIZE_INPUT_STRING);
    len = strlen(instg);
    if (instg[len - 1] == '\n') instg[len - 1] = 0;
//    printf("string is %s \n", instg);

    substring = strtok(instg, " ");
    strcpy(the_tag, substring);
//    printf("first substring is %s\n", the_tag);
    substring = strtok(NULL," ");
    strcpy(the_value, substring);
//    printf("second substring is %s\n", the_value);

    if (strcmp(the_tag, "physical:") == 0)
      {
      count_physical += 1;
      }
    else if (strcmp(the_tag, "logical:") == 0)
      {
      count_logical += 1;
      }
    else if(strcmp(the_tag, "length:") == 0)
      {
      int_value = atoi(the_value);
      /* note that we will have two sets of logical strings
         each with its own set of leds
         and we need to account for the leds in the physical string */
      count_led += int_value; 
      count_physical_leds += int_value;
      }
    }

//  printf(" phy %d log %d leds %d\n", count_physical,
//    count_logical, count_led);

  number_physical_strings = count_physical;
  number_logical_strings = count_logical;
  number_leds = count_led;
  number_physical_string_leds = count_physical_leds;
  fclose (fpconfig);
  return 0;
  }

/* Opens and parses the config file to populate 
   the physical and logical strings */

int parse_and_fill(char *filename)
  {
  FILE *fpconfig = NULL;
  char instg[SIZE_INPUT_STRING];
  char *cpres;
  char *substring;
  
  int len;
  int count_physical = 0; /* number of physical strings in garment */
  int count_logical = 0; /* total number of logical strings in garment */
  int count_logical_in_physical = 0; /* number of logical strings in
                                        this physical string */
  int count_leds_in_physical = 0; /* total number of leds in this physical string */
  int current_logical_start_position = 0; /* start led in current logical */
  int int_value = 0; /* value returned by atoi */

  char the_tag[30];
  char the_value[30];
  
  led_type *current_led = NULL;
  led_type *current_physical_led = NULL;
  physical_string_type *current_physical = NULL;
  logical_string_type *current_logical = NULL;

  enum state_we_are_in_type our_state = physical;

  if ((fpconfig = fopen(filename, "r")) == NULL)
    {
    printf("cannot open config file\n");
    return -1;
    }
    
  current_led = leds; /* these are leds in the logical strings */
  current_physical = physical_strings;
  current_logical = logical_strings;
  current_physical_led = physical_string_leds;

  while ((cpres = fgets(instg, SIZE_INPUT_STRING, fpconfig)) != NULL)
    {
    force_lower(instg, SIZE_INPUT_STRING);
    len = strlen(instg);
    if (instg[len - 1] == '\n') instg[len - 1] = 0;
    printf("string is %s \n", instg);

    substring = strtok(instg, " ");
    strcpy(the_tag, substring);
//    printf("first substring is %s\n", the_tag);
    substring = strtok(NULL," ");
    strcpy(the_value, substring);
//    printf("second substring is %s\n", the_value);

    if (strcmp(the_tag, "physical:") == 0)
      {
      our_state = physical;
      if (count_physical > 0) 
        /* close current if we are not at very
           beginning of garment */
        {
        current_physical->string_length = count_leds_in_physical;
        current_physical->nbr_log_strings = count_logical_in_physical;
        current_physical->string_leds = current_physical_led;
        current_physical_led += current_physical->string_length;
        current_physical += 1;
        }
      /* Fill in the name of the physical */
      current_physical->log_string = current_logical;
      count_leds_in_physical = 0;
      count_logical_in_physical = 0;
      current_logical_start_position = 0;
      strncpy(current_physical->name, the_value, NAME_LENGTH);
      count_physical += 1;
      }
    else if (strcmp(the_tag, "logical:") == 0)
      {
      our_state = logical;
      count_logical += 1;
      count_logical_in_physical += 1;
      /* Note that each logical string has cuurent and working;
         which means it takes up two logical string memory spaces */
      current_logical = logical_strings + (count_logical - 1);
      strncpy(current_logical->name, the_value, NAME_LENGTH);
      current_logical->start_location = current_logical_start_position;
      current_logical->string_leds = current_led;
      }
    else if ((strcmp(the_tag, "length:") == 0) && (our_state == logical))
      {
      int_value = atoi(the_value);
      current_logical->length = int_value;
      current_led += current_logical->length;
      current_logical_start_position += current_logical->length;
      count_leds_in_physical += current_logical->length;
      }
    else if ((strcmp(the_tag, "direction:") == 0) && (our_state == logical))
      {
      int_value = atoi(the_value);
      current_logical->direction = int_value;
      }
    else if ((strcmp(the_tag, "data:") == 0) && (our_state == physical))
      {
      int_value = atoi(the_value);
      current_physical->gpio_data_pin = int_value;
      }
    else if ((strcmp(the_tag, "clock:") == 0) && (our_state == physical))
      {
      int_value = atoi(the_value);
      current_physical->gpio_clock_pin = int_value;
      }
    }
  /* Done with loop; fill out last physical string totals */
  current_physical->string_length = count_leds_in_physical;
  current_physical->nbr_log_strings = count_logical_in_physical;
  current_physical->string_leds = current_physical_led;
  current_physical_led += current_physical->string_length;

  fclose (fpconfig);
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

  res = count_leds_and_strings(*(argv + 1));
  if (res != 0)
    {
    printf("could not open/process config file\n");
    exit(1);
    }

  setup_memory();
  parse_and_fill(*(argv + 1));
  }
