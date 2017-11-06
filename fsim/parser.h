#pragma once
#include "object.h"


object_t *parse_string(const char *text);

object_t *parse_file(const char *file_name);
