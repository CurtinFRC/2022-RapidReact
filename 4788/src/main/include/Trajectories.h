#include "Trajectory.h"

struct Trajectories {
  ::Trajectory test{{{0.8,-3.3}, {0,0}, {1,1}, {5.5,0.9}}};

  void build() {
    test.build();
  }
};