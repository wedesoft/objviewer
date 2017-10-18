#pragma once
#include "munit.h"


extern int width;
extern int height;

void write_ppm(const char *file_name, int width, int height, unsigned char *data);

unsigned char *read_pixels(void);

void* test_setup_gl(const MunitParameter params[], void* user_data);
