#ifndef LINEAR_PATH_H
#define LINEAR_PATH_H

#include "GenericPathing.h"

namespace TreasureMapper {
	class Linear : private GenericPathing {
		public:
			struct Line2D : public Path2D {
				struct Crosses {
					std::vector<Point> points;
				};
				Crosses crosses;

				double getLineLength(Line2D line);
				double getLineAngle(Line2D line, bool radians = false);
			};
	};
}

#endif