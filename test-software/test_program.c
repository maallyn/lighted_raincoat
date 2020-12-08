#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <wiringPi.h>

#define DATA1 2
#define CLOCK1 3

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

int main(int argc, char **argv)
{
printf("Hello out there\n");
}
