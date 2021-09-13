#ifndef _LIGHTED_H
#define _LIGHTED_H 1

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

/* Function definitions */
void force_lower(char *this_stg, int this_size);
void setup_memory();
void setup_physical_string_gpio_pins();
void send_physical_string(physical_string_type *physical_string);
void load_physical_string(physical_string_type *physical_string);
int count_leds_and_strings(char *filename);
int parse_and_fill(char *filename);
void print_arrays(void);




/* Global data; all and LED strings for entire garment */
extern physical_string_type *physical_strings;
extern int number_physical_strings;
extern logical_string_type *logical_strings;
extern int number_logical_strings;
extern led_type *leds;
extern int number_leds;
extern led_type *physical_string_leds;
extern int number_physical_string_leds;

#endif /* _LIGHTED_H */
