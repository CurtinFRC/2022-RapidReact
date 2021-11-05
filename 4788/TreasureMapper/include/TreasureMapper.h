#ifndef TREASUREMAPPER_H
#define TREASUREMAPPER_H

#include "ShipControl.h"
#include "utilities/genericHeaders.h"

namespace TreasureMap {
	class TreasureMapper : public ShipControl {
	 public:
		TreasureMapper(Config &config);
		~TreasureMapper();

		Path::lPath buildPath(lPath path, double startAngle, double endAngle);

		bool followPath(lPath *path, double dt, bool reverse);

		// buildPath(lPath path, double startAngle, double endAngle);

		double getCurrentLocation(Config &config, bool inMeters);

		Config *getConfig() {
			return &_config;
		}

	 private:
		void linearDrive(lPath *path, double dt, bool reverse);
		Config &_config;
		bool _disableAngleSE = false;
		int _currentLine = 0;
	};
}

#endif 