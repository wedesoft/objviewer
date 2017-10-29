#pragma once
#define _GNU_SOURCE
#define __USE_GNU
#include <search.h>


typedef struct {
  struct hsearch_data table;
} hash_t;

hash_t *make_hash(void);

int hash_find(hash_t *hash, int key, int value_if_not_found);
