#include "Trajectory.h"

struct Trajectories {
  ::Trajectory test{{{1,-3}, {0,0}, {1,1}, {5.5,1}}};

  void build() {
    test.build();
  }
};