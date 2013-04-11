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


template <class T>
class PCMBuffer {

public:
  PCMBuffer(double frequency, int channels);

private:
  T *buf_;
  size_t len_;
  int channels_;

  class Channel {
    private:
      T *buf_;
      int offset_;

    public:
      Channel(PCMBuffer *buf, int offset) : buf_(&(buf->buf_[offset])), offset_(offset) { };

  };
};

#endif
