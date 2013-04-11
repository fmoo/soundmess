#include "AODevice.h"

#include <iostream>
#include <cstring>
#include <sys/time.h>
#include <unistd.h>

double MIDDLE_C = 261.626;


double doubletime() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  //printf("%ld.%.6ld\n", tv.tv_sec, tv.tv_usec);
  return (double)tv.tv_sec + ((double)tv.tv_usec / 1000000.0);
}

void initBuffer(buf_t *buf) {
  // 1 second of 2 channel, 16-bit audio at 44.1kbps
  for (int i = 0; i < buf->len / 2; i++) {
    buf->data16[i] = -0x0010;
    //buffer[i] = 0x0000;
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
  initBuffer(&buf);

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
