#ifndef BUF_H
#define BUF_H

#include <stdint.h>

typedef struct {
  union {
    int8_t *data8;
    int16_t *data16;
  };
  size_t len8;
  size_t len16;
} buf_t;

#endif
