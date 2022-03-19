#include "include/lighted.h"


/* testing functions */
void rotate_led(led_type *this_led)
  {
  if (this_led->red_byte < 15)
    {
    this_led->red_byte += 1;
    }
  else
    {
    this_led->red_byte = 0;
    if (this_led->green_byte < 15)
      {
      this_led->green_byte += 1;
      }
    else
      {
      this_led->green_byte = 0;
      if (this_led->blue_byte < 15)
        {
        this_led->blue_byte += 1;
        }
      else
        {
        this_led->blue_byte = 0;
        }
      }
    }
  }


int main(int argc, char **argv)
  {
  int res = 0;

  /* Testing data */
  static led_type test_led;

  static led_type *current_led;

  static logical_string_type *current_logical;

  static physical_string_type *current_physical;

  static int phys_count, log_count, led_count = 0;

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
  setup_physical_string_gpio_pins();

  /* Testing */

  while(1)
  {
  for (phys_count = 0; phys_count < number_physical_strings;
       phys_count += 1)
    {
    current_physical = physical_strings + phys_count;
    for (log_count = 0; log_count < current_physical->nbr_log_strings;
         log_count += 1)
      {
      current_logical = current_physical->log_string+log_count;
      for (led_count = 0; led_count < current_logical->length;
           led_count += 1)
        {
        current_led = current_logical->string_leds+led_count;
        current_led->red_byte = test_led.red_byte;
        current_led->blue_byte = test_led.blue_byte;
        current_led->green_byte = test_led.green_byte;
        rotate_led(&test_led);
        }
      }
    load_physical_string(current_physical);
    send_physical_string(current_physical);
    }
  }
  }
