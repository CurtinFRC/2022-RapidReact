#include "Trajectory.h"

struct Trajectories {
  ::Trajectory test{{{0,0}, {2,0}, {4,2}, {6,2}}};

  void build() {
    test.build();
  }
};