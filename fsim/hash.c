#include <stdio.h>
#include <search.h>
#include <gc.h>
#include "hash.h"


void hash_create(int size)
{
  hcreate(size);
}

void hash_enter(int key, int value)
{
  long int lvalue = value;
  ENTRY item = {GC_MALLOC_ATOMIC(10), (void *)lvalue};
  snprintf(item.key, 10, "%d", key);
  hsearch(item, ENTER);
}

int hash_find(int key)
{
  ENTRY item = {GC_MALLOC_ATOMIC(10), NULL};
  snprintf(item.key, 10, "%d", key);
  ENTRY *result = hsearch(item, FIND);
  return result ? (long int)result->data : -1;
}

void hash_destroy(void)
{
  hdestroy();
}
