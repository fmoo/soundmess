#include <iostream>
#include <cstring>
#include <sys/time.h>
#include <unistd.h>
#include <cmath>

#include "AODevice.h"
#include "ftimer.h"

double MIDDLE_C = 261.626;
double MIDDLE_C_PERIOD = 1.0 / MIDDLE_C;


double doubletime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  //printf("%ld.%.6ld\n", tv.tv_sec, tv.tv_usec);
  return (double)tv.tv_sec + ((double)tv.tv_usec / 1000000.0);
}

void initBuffer(buf_t *buf, const int rate) {
  FTimer ft(rate);
  double amp = 0x7fff;
  for (int i = 0; i < buf->len16; i += 2) {
    double t = ft.getTime();
    double _garbage;

    // hack divide by 2 to accommodate 2-channel audio ?
    double t0 = modf(t / MIDDLE_C_PERIOD, &_garbage);

    // sawtooth
    buf->data16[i] = (fabs(t0 - 0.5) - 0.25) * 4 * 0x7fff;
    buf->data16[i + 1] = (fabs(t0 - 0.5) - 0.25) * 4 * 0x7fff;

    // square
    //buf->data16[i] = 0x7fff * (t0 > 0.5 ? 1 : -1);
    ft.tick();
  }
}


void sleepd(double amount) {
  struct timespec ts;
  ts.tv_sec = (int)amount;
  ts.tv_nsec = (amount - ts.tv_sec) * 1000000000.0;
  nanosleep(&ts, NULL);
}


int main(int argc, char **argv) {
  AODevice ao;
  ao.open();

  buf_t buf = ao.makeBuffer(5.0);
  initBuffer(&buf, ao.getSamplingRate());

  double t0 = doubletime();
  printf("Playing buffer...");
  fflush(stdout);
  ao.play(&buf);
  printf("ao.play took %.3fs\n", doubletime() - t0);
  printf("Sleeping for 3 seconds...");
  fflush(stdout);
  sleepd(3);
  printf("done\n");

  return 0;
}
