#include <string.h>
#include <stdio.h>
#include <gc.h>
#include "hash.h"


static void finalize_hash(GC_PTR obj, GC_PTR env)
{
  hash_t *result = (hash_t *)obj;
  hdestroy_r(&result->table);
}

hash_t *make_hash(void)
{
  hash_t *result = GC_MALLOC(sizeof(hash_t));
  GC_register_finalizer(result, finalize_hash, 0, 0, 0);
  memset(result, 0, sizeof(hash_t));
  hcreate_r(65536, &result->table);
  return result;
}

static int hash_find_str(hash_t *hash, char *key, int value_if_not_found)
{
  long int value = value_if_not_found;
  ENTRY item = {key, (void *)value};
  ENTRY *result;
  hsearch_r(item, ENTER, &result, &hash->table);
  return (long int)result->data;
}

int hash_find(hash_t *hash, int key1, int key2, int key3, int value_if_not_found)
{
  char *str = GC_MALLOC_ATOMIC(13);
  snprintf(str, 20, "%d,%d,%d", key1, key2, key3);
  return hash_find_str(hash, str, value_if_not_found);
}
