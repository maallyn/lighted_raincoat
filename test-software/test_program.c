#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <wiringPi.h>

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
  logical_string_type *log_strings;
  };

typedef struct physical_string_struct physical_string_type;

/* Global data; all strips and LED strings for entire garment */
static strip_type *strips = NULL;
static int number_strips = 0;
static physical_string_type *physical_strings = NULL;
static int number_physical_strings = 0;
static logical_string_type *logical_strings = NULL;
static int number_logical_strings = 0;

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


int main()
  {
  int strip = 0;
  setup();
  while(TRUE) {
    send_byte((unsigned char)0xaa, strip);
    }
  }
