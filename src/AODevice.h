#ifndef AODEVICE_H
#define AODEVICE_H

#include <stdint.h>
#include <ao/ao.h>
#include "buf.h"

class AODevice {
  public:
    AODevice();
    ~AODevice();

    void open();
    int play(char *output_samples, uint32_t num_bytes);
    int play(buf_t *buf);
    buf_t makeBuffer(double duration);
    const int getSamplingRate() { return bitrate_; };

  private:
    ao_device *device_;
    int bitrate_;
    int bitsPerSample_;
    int channels_;
    char *matrix_;
    bool opened_;
    int byteFormat_;
};

#endif
