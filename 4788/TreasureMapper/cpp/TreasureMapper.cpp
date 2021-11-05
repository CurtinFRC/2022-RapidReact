#include "TreasureMapper.h"

namespace TreasureMap {
	TreasureMapper::TreasureMapper(Config &config) : _config(config) { 
		//print config stuff
	}

	Path::lPath TreasureMapper::buildPath(lPath path, double startAngle, double endAngle) {
		double totalLength = 0;
		for (size_t i = 0; i < path.lines.size(); i++) {
			path.lines[i].length = getLineLength(path.lines[i]);
			path.lines[i].angle = getLineAngle(path.lines[i]);

			std::cout << "Line " << i << " length: " << path.lines[i].length << std::endl;
			std::cout << "Angle " << i << " angle: " << path.lines[i].angle << std::endl;

			totalLength += path.lines[i].length;
			path.lines[i].totalLength = totalLength;
		}

		PathState newState;
		newState.setState(PathState::State::kStartAngle);

		path.pathStartAngle = startAngle;
		path.pathEndAngle = endAngle;
		path.pathState = newState;
		path.pathLength = totalLength;

		std::cout << "Total length: " << totalLength << std::endl;
		return path;
	}

	void TreasureMapper::linearDrive(lPath *path, double dt, bool reverse) {
		//linear sail? 
		if ((size_t)_currentLine > path->lines.size()) {
			_config.drivetrain->Set(0,0);
			path->pathState.setState(PathState::State::kPathComplete);
		} else {
			if (driveToTarget(path, _currentLine, reverse, dt, _config)) {
				_currentLine += 1;
			}
		}
	}

	bool TreasureMapper::followPath(lPath *path, double dt, bool reverse) {
		if (_disableAngleSE) {
			linearDrive(path, dt, reverse);
		} else {
			switch (path->pathState.state) {
				case PathState::State::kStartAngle: 
					if (turn2Angle(path->pathStartAngle, dt, _config, true)) {
						path->pathState.setState(PathState::State::kSplineFollow);
					}
					break;

				case PathState::State::kSplineFollow:
					linearDrive(path, dt, reverse);
					break;

				case PathState::State::kEndAngle:
					if (turn2Angle(path->pathEndAngle, dt, _config, true)) {
						path->pathState.setState(PathState::State::kPathComplete);
					}
					break;
				
				case PathState::State::kPathComplete:
					break;
			}
		}
		
		
		return path->pathState.getPathComplete();
	}

	double TreasureMapper::getCurrentLocation(Config &config, bool inMeters) {
		double location = inMeters ? currentLocation_M(config) : currentLocation_R(config);
		return location;
	}
}