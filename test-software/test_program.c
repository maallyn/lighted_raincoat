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


int main(int argc, char **argv)
  {
  int strip = 0;
  setup();
  while(TRUE) {
    send_byte((unsigned char)0xaa, strip);
    }
  }
