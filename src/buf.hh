#ifndef BUF_H
#define BUF_H

#include <stdint.h>

typedef struct {
  union {
    int8_t *data8;
    int16_t *data16;
  };
  size_t len;
} buf_t;

#endif
