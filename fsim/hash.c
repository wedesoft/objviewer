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

int hash_find(hash_t *hash, int key, int value_if_not_found)
{
  long int value = value_if_not_found;
  ENTRY item = {GC_MALLOC_ATOMIC(6), (void *)value};
  snprintf(item.key, 6, "%d", key);
  ENTRY *result;
  hsearch_r(item, ENTER, &result, &hash->table);
  return (long int)result->data;
}
