#include "Drivetrain.h"
#include "Path.h"
#include "NTProvider.h"
#include "utilities/genericHeaders.h"

namespace TreasureMap {
	class ShipControl : public Path {
	 public:
		struct Config {
			wml::Drivetrain *drivetrain;
			bool invertLeftENC = false;
			bool invertRightENC = false;

			double *dp_drive,
			*ki_drive,
			*kd_drive,

			*kp_turn,
			*ki_turn,
			*kd_turn,

			gearBoxReduction = 0,
			wheelDiameter = 0, //measured in Meters
			maxSpeed = 0, //maybe i should limit this
			maxTurnSpeed = 0; 

			bool dynamicLimits = false;
		};

		void setBarStop(Config &config, double bar, bool meters = false) {
			if (meters) {
				_bar = (bar/(A_PI*config.wheelDiameter));
			} else {
				_bar = bar;
			}
		}

		void setAnglePrc(double anglePrc = 2) {
			_anglePrc = anglePrc;
		}

		void resetLoop();

		void testDrivePID(double dt, Config &config, double meters2drive = 2);

		void testTurnPID(double dt, Config &config, double angle2turn);

		void testPID(double dt, Config &config, double meters2drive = 2, double angle2turn = 90);

		double getCurrentLocation(Config &config, bool meters, bool wheelRotations);

		void setWrap(double range) {
			_wrapRange = range;
		}

		double wrap(double val) {
			if (_wrapRange > 0) {
				val = std::fmod(val, _wrapRange);
				if (std::abs(val) > (_wrapRange/2.0)) {
					return (val > 0) ? val - _wrapRange : val + _wrapRange;
				}
			}
			return val;
		}

	 protected:
		bool driveToTarget(lPath *path, int line, bool reverse, double dt, Config &config);
		bool turn2angle(double angle, double dt, Config &config, bool noPID);

		double currentLocation_M(Config &config);
		double currentLocation_R(Config &config, bool wheelRotations);

	 private:
		double rotationsToTarget(lLine line, Config &config, bool wheelRotations);
		double internalPID(double dt, double goal, double input, Config &config, bool turnLoop);
		double gyroFollow(lLine line, double dt, Config &config);

		void valueLimit(double &value, double limit = 1, bool dynamic = false) {
			if (dynamic) {
				value *= limit;
			} else {
				value = std::max(value, -limit);
				value = std::min(value, limit);
			}
		}
	
	 private:
		double _goal = 0;
		double _previousError = 0;
		double _sum = 0;
		bool _pathComplete = false;

		double _wrapRange = -1;
		double _rotationsToTarget = 0;
		double _bar = 0;
		double _anglePrc = 2;
	};
}

//so whos julia? -> sister apparently 