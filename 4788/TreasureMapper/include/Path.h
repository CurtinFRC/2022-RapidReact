//!change this later 

#include <vector>
#include <math.h>
#include <iostream>
#include <string>
#include "utilities/genericHeaders.h"


namespace TreasureMap {
	class Path {
	 public:
		struct PathState {
			enum class State {
				kStartAngle = 0,
				kSplineFollow,
				kEndAngle,
				kPathComplete
			}; State state;

			void setState(State st) {
				state = st;
			}

			State getState() {return state; }
			bool getPathComplete() {
				if (getState() == State::kPathComplete) {
					return true;
				} else {
					return false;
				}
			}
		};

		struct lPoint {
			double x, y;
		};

		struct lLine {
			lPoint points[2];
			double angle = 0,
						 length = 0,
						 totalLength = 0;
			bool complete = false;
			bool negativeLine = false, semiNegativeLine = false;
		};

		struct lPath {
			std::vector<lLine> lines;
			double pathLength = 0, //in meters
						 pathStartAngle = 0,
						 pathEndAngle = 0;
			PathState pathState;
			std::string name = ""; //i should make poggies default for this 
		};

		double getLineLength(lLine line);
		double getLineAngle(lLine line, bool radians = false);

	 private:
		double _stepSize = 0.005f;
	};
}