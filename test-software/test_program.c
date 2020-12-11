#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <wiringPi.h>

#define DATA1 2
#define CLOCK1 3
#define LED_START 0xfe

struct led_struct
  {
  unsigned char blue_byte;
  unsigned char green_byte;
  unsigned char red_byte;
  };

typedef struct led_struct led_type;

struct physical_string_struct
  {
  int string_length;
  int strip;
  led_type *string_leds;
  };

typedef struct physical_string_struct physical_string_type;

struct logical_string_struct
  {
  int direction;
  int length;
  int start_location;
  led_type *string_leds;
  };

typedef struct logical_string_struct logical_string_type;

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
    digitalWrite(CLOCK1, HIGH);
    /* set data to whichever, based on the bit */
    if ((workval & 0x80) == 0)
      {
      digitalWrite(DATA1, HIGH);
      }
    else
      {
      digitalWrite(DATA1, LOW);
      }
    /* wait 5 us and then set clock to high */
    /* low to high transition is what clocks data in */
    delayMicroseconds(5);
    digitalWrite(CLOCK1, LOW);
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

physical_string_type *allocate_physical_string(int string_length)
  {
  physical_string_type *working_physical;
  led_type *working_leds;

  if ((working_leds = calloc(sizeof(led_type) * string_length, 1)) == NULL)
    {
    return NULL;
    }

  else
    {
    if ((working_physical = calloc(sizeof(physical_string_type), 1)) == NULL)
      {
      free(working_leds);
      return NULL;
      }
    else
      {
      working_physical->string_leds = working_leds;
      working_physical->string_length = string_length;
      return(working_physical);
      }
    }
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


int main(int argc, char **argv)
  {
  int strip = 0;
  setup();
  while(TRUE) {
    send_byte((unsigned char)0xaa, strip);
    }
  }
