#include "AODevice.h"

#include <stdint.h>
#include <ao/ao.h>
#include "buf.h"

static bool initialized = false;

AODevice::AODevice() : device_(NULL), bitrate_(44100),
      bitsPerSample_(16), channels_(2), matrix_((char *)"L,R"),
      opened_(false), byteFormat_(AO_FMT_NATIVE) { }

AODevice::~AODevice() {
  if (device_ && opened_) {
    ao_close(device_);
  }
}

void AODevice::open() {
  if (!initialized) {
    ao_initialize();
    initialized = true;
  }

  // driver_id
  int default_driver_id = ao_default_driver_id();

  // Other shit
  ao_sample_format samplefmt;
  ao_option *option_list = NULL;

  samplefmt.bits = bitsPerSample_;
  samplefmt.rate = bitrate_;
  samplefmt.channels = channels_;
  samplefmt.matrix = matrix_;
  samplefmt.byte_format = byteFormat_;

  device_ = ao_open_live(
    default_driver_id,
    &samplefmt,
    option_list
  );
  opened_ = true;
}

int AODevice::play(char *output_samples, uint32_t num_bytes) {
  return ao_play(device_, output_samples, num_bytes);
}

int AODevice::play(buf_t *buf) {
  return play((char *)buf->data8, buf->len8);
}

buf_t AODevice::makeBuffer(double duration) {
  buf_t result;
  result.len8 = (size_t)(duration * bitsPerSample_ / 8.0 * bitrate_ * channels_);
  result.data8 = (int8_t *)malloc(result.len8);
  result.len16 = result.len8 / 2;
  return result;
}
