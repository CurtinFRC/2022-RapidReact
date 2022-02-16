#include "Trajectory.h"

struct Trajectories {
  ::Trajectory test{{{1,-3}, {0,0}, {0.8,0.8}, {1.5,2}, {1,7.5}}};
  // ::Trajectory test{{{0,0}, {3,0}, {1,-1}, {0,-3}}};

  void build() {
    test.build();
  }
};