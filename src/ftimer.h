#ifndef FTIMER_H
#define FTIMER_H


class FTimer {
  public:
    FTimer(double frequency) : frequency_(frequency), time_(0),
      increment_(1.0 / frequency_) {
    }

    const double getTime() { return time_; };
    double tick() {
      time_ += increment_;
      return time_;
    }

  private:
    double frequency_;
    double increment_;
    double time_;
};

#endif
