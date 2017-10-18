#pragma once


typedef struct
{
  int width;
  int height;
  unsigned char *data;
} image_t;

image_t *read_image(const char *file_name);
