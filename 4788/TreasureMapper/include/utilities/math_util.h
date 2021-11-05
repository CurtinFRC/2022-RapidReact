#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include <math.h>
#include <vector>
#include <string>
#include <tuple>
#include <iostream>
#include <utility>

#define A_PI	3.14159265358979323846   // Anna pi 

namespace TreasureMap {
	struct MathUtils {

		static double r2d(double angle) {
			return angle * 180 / A_PI;
		}

		static double d2r(double angle) {
			return angle * A_PI / 180;
		}
	};
}

#endif