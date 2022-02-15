#pragma once

class Debounce {
 public:
  Debounce(double time) : _time(time) {
    _lastChange = 0;
    _lastState = 0;
  }

  bool Get(bool current) {
    double now = (double)frc::Timer::GetFPGATimestamp();

    //rising edge
    if (current != _lastState) {
      _lastChange = now;
      _lastState = current;
    }

    if (now > _lastChange + _time) {
      return current;
    } else {
      return false;
    }
  }
 private:
  bool _lastState;
  double _lastChange, _time;
};