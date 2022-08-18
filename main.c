#include <stdio.h>
#include "./include/globals.h"

// Be very suspicious of any macro that attempts to extend language syntax;
// it's always a hack, and almost always has a fatal weakness or two.
// But I'm doing it anyways, lol.
#define foreach(item, array) \
  for(int keep = 1, count = 0, size = sizeof (array) / sizeof *(array); \
	keep && count != size; \
	keep = !keep, count++) \
	for(item = (array) + count; keep; keep = !keep)

void f() {
  int test[] = {1,2,3,4,5};
  foreach(int *v, test) {
    printf("value: %d\n", *v);
  }
}

int main(void) {
  printf("Hello, world\n");
  f();
  return 0;
}
