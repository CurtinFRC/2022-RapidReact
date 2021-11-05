#ifndef PATHHEADERS_H
#define PATHHEADERS_H

#include "utilities/genericHeaders.h"

namespace TreasureMapper {
	struct GenericPathing {
		struct Path2D {
			struct Point {
				double x,y;
			};

			struct TangentPoint {
				Point p1, p2, t1, t2;
			};
		};
	};
}

#endif