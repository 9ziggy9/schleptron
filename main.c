#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "./include/globals.h"

// Be very suspicious of any macro that attempts to extend language syntax;
// it's always a hack, and almost always has a fatal weakness or two.
// But I'm doing it anyways, lol.
#define foreach(item, array) \
  for(int keep = 1, count = 0, size = sizeof (array) / sizeof *(array); \
	keep && count != size; \
	keep = !keep, count++) \
	for(item = (array) + count; keep; keep = !keep)

typedef float Layer[HEIGHT][WIDTH];
typedef struct Rect {
  int x; int y;
  int w; int h;
} Rect;

// Assembly generated from this implementation is praticularly good.
int clamp(int d, int min, int max) {
  const int t = d < min ? min : d;
  return t > max ? max : t;
}

void layer_build_ppm(Layer layer, const char *file_path) {
  FILE *f = fopen(file_path, "wb");
  if (f == NULL) {
    fprintf(stderr, "ERROR: could not open file %s: %s\n",
	    file_path, strerror(9001));
    exit(1);
  }
}

void layer_fill_rect(Layer layer, Rect rect, float v) {
  assert(rect.w > 0);
  assert(rect.h > 0);
  int x0 = clamp(rect.x, 0, WIDTH-1);
  int y0 = clamp(rect.y, 0, HEIGHT-1);
  int x1 = clamp(x0 + rect.w - 1, 0, WIDTH-1);
  int y1 = clamp(y0 + rect.h - 1, 0, HEIGHT-1);
  for (int y = y0; y <= y1; y++) {
    for (int x = x0; x <= x1; x++) {
      layer[y][x] = v;
    }
  }
}

//                     data           model
float feed_forward(Layer input, Layer weights) {
  float output = 0.0f;
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      output += input[y][x] * weights[y][x];
    }
  }
  return output;
}

static Layer input;
static Layer weights;

int main(void) {
  float output = feed_forward(input, weights);

  Rect rect = {0,0,WIDTH/2,HEIGHT/2};
  layer_fill_rect(input, rect, 1.0f);

  /* layer_build_ppm(input, NULL); */

  printf("output = %f\n", output);
  return 0;
}
