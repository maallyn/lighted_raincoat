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
  }
