#include "paths/Linear.h"

namespace TreasureMapp {
	double Linear::Line2D::getLineLength(Line2D line) {
		double lengthSqr = pow((line.crosses.points[1].x - line.crosses.points[0].x), 2) + 
											 pow((line.crosses.points[1].y - line.crosses.points[0].y), 2);
		return sqrt(lengthSqr);
	}

	double Linear::Line2D::getLineAngle(Line2D line, bool radians) {
		double dy = line.crosses.points[1].y - line.crosses.points[0].y;
		double dx = line.crosses.points[1].x - line.crosses.points[0].x;
		double theta = atan2(dy, dx); //range (-pi, pi)

		if (!radians) {
			theta *= 180 / A_PI;
		}

		return theta;
	}
}