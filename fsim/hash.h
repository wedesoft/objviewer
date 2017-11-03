#pragma once
#define _GNU_SOURCE
#define __USE_GNU
#include <search.h>
#include "material.h"


typedef struct {
  struct hsearch_data table;
} hash_t;

hash_t *make_hash(void);

int hash_find_index(hash_t *hash, int key1, int key2, int key3, int value_if_not_found);

material_t *hash_find_material(hash_t *hash, const char *key, material_t *material);
