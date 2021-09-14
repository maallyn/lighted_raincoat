#include "include/lighted.h"

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
  print_arrays();
  /* Testing */
  led_type *this_led = NULL;
  logical_string_type *this_logical = NULL;
  physical_string_type *this_physical = NULL;

  unsigned char this_red = 0;
  unsigned char this_blue = 0;
  unsigned char this_green = 0;

  int physical_count = 0;
  int logical_count = 0;
  int led_count = 0;

  this_physical = physical_strings;
  }
