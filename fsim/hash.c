#include <stdio.h>
#include <search.h>
#include <gc.h>
#include "hash.h"


void hash_create(void)
{
  hcreate(65536);
}

int hash_find(int key, int value_if_not_found)
{
  long int value = value_if_not_found;
  ENTRY item = {GC_MALLOC_ATOMIC(6), (void *)value};
  snprintf(item.key, 6, "%d", key);
  return (long int)hsearch(item, ENTER)->data;
}

void hash_destroy(void)
{
  hdestroy();
}
