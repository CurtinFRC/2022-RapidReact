#include "Path.h"

namespace TreasureMap {
	double Path::getLineLength(lLine line) {
		double lengthSqr = pow((line.points[1].x - line.points[0].x), 2) + pow((line.points[1].y - line.points[0].y), 2);
		return sqrt(lengthSqr);
	}

	double Path::getLineAngle(lLine line, bool radians) {
		double x1 = line.points[0].x;
		double y1 = line.points[0].y;

		double x2 = line.points[1].x;
		double y2 = line.points[1].y;

		double dy = y2 - y1;
		double dx = x2 - x1;
		double theta = atan2(dy, dx);

		if (x2 < x1 && y2 < y1) {
			line.negativeLine = true;
		} 

		if (y2 > y1) {
			line.semiNegativeLine = true;
		}

		if (!radians) {
			theta *= 180 / A_PI;
		}

		if (line.semiNegativeLine && !line.negativeLine) {
			theta = -theta;
		}

		if (line.negativeLine && !line.semiNegativeLine) {
			theta = (theta + (-90));
		}

		if (!line.negativeLine && !line.semiNegativeLine) {
			theta = -theta;
		}

		if (line.negativeLine && line.semiNegativeLine) {
			theta = (theta + (-90));
		}
		return theta;
	}
}

//gradients -> for ruben 