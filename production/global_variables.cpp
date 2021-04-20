#include "include/lighted.h"

/* Global data; all and LED strings for entire garment */
physical_string_type *physical_strings = NULL;
int number_physical_strings = 0;
logical_string_type *logical_strings = NULL;
int number_logical_strings = 0;
led_type *leds = NULL;
int number_leds = 0;
led_type *physical_string_leds = NULL;
int number_physical_string_leds = 0;
