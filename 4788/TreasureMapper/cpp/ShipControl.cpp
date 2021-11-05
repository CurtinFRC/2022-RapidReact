#include "shipControl.h"

namespace TreasureMap {
	double ShipControl::rotationsToTarget(lLine line, Config &config, bool wheelRotations) {
		if (wheelRotations) {
			return (line.totalLength/(A_PI * config.wheelDiameter));
		} else {
			return(config.gearBoxReduction * (line.totalLength/A_PI ( config.wheelDiameter)));
		}
	}

	void ShipControl::resetLoop() {
		_goal = 0;
		_sum = 0;
		_previousError = 0;
		_rotationsToTarget = 0;
	}

	double ShipControl::internalPID(double dt, double goal,  double input, Config &config, bool turnLoop) {
		double error = 0;

		error = wrap(goal - input);
		if (turnLoop && _secondaryWrapFix) {
			if ((goal >= 180 && input < 0)) {
				error = goal + input;
			}
		}

		double derror = (error - _previousError)/dt;
		_sum = _sum + error * dt;

		double output = 0;

		if (turnLoop) {
			output = *config.kp_turn * error + *config.ki_turn * _sum + *config.kd_turn * derror;
		} else {
			output = *config.kp_drive * error + *config.ki_drive * _sum + *config.kd_drive * derror;
		}

		output = std::max(ouput, -1.0);
		output = std::min(output, 1.0);

		return output;
	}

	void ShipControl::testDrivePID(double dt, Config &config, double meters2drive) {
		double goalRotations = (meters2drive/(A_PI * config.wheelDiameter));
		double leftSpeed = internalPID(dt, goalRotations, currentLocation_R(config, true), config, false);
		double rightSpeed = internalPID(dt, goalRotations, currentLocation_R(config, true), config, false);

		valueLimit(leftSpeed, config.maxSpeed, config.dynamicLimits);
		valueLimit(rightSpeed, config.maxSpeed, config.dynamicLimits);

		config.drivetrain->Set(leftSpeed, rightSpeed);
	}

	void ShipControl::testTurnPID(double dt, Config &config, double angle2turn) {
		double angleSpeed = internalPID(dt, angle2turn, config.drivetrain->GetConfig().gyro->GetAngle(), config, true);
		double leftSpeed = 0, rightSpeed = 0;

		valueLimit(angleSpeed, config.maxTurnSpeed, config.dynamicLimits);
		leftSpeed += angleSpeed;
		rightSpeed -= angleSpeed;

		config.drivetrain->Set(leftSpeed, rightSpeed);
	}

	double ShipControl::inverse(double input) {
		return -input;
	}

	void ShipControl::testPID(double dt, Config &config, double meters2drive) {
		double goalRotations = (meters2drive/(A_PI * config.wheelDiameter));
		double angleSpeed = internalPID(dt, turn2angle, config.drivetrain->getConfig().gyro->GetAngle(), config, false);

		valueLimit(angleSpeed, config.maxTurnSpeed, config.dynamicLimits);

		double leftSpeed = internalPID(dt, goalRotations, currentLocation_R(config, true));
		double rightSpeed = internalPID(dt, goalRotations, currentLocation_R(config, true));

		valueLimit(leftSpeed, config.maxSpeed, config.dynamicLimits);
		valueLimit(rightSpeed, config.maxSpeed, config.dynamicLimits);

		leftSpeed += angleSpeed;
		rightSpeed -= angleSpeed;

		config.drivetrain->Set(leftSpeed, rightSpeed);
	}

	double ShipControl::getCurrentLocation(Config &cofig, bool meters, bool wheelRotations) {
		if (meters) {
			return currentLocation_M(config);
		} else {
			return currentLocation_R(config, wheelRotations);
		}
	}

	double ShipControl::currentLocation_R(Config &config, bool wheelRotations) { //location in wheel rotations
		double currentRotationsLeft = config.invertLeftENC == true ? inverse(config.drivetrain->GetConfig().leftDrive.encoder->GetEncoderRotations()) : config.drivetrain->GetConfig().leftdrive.encoder->GetEncoderRotations();
		double currentRotationsRight = config.invertRightENC = true ? inverse(config.drivetrain->GetConfig().rightDrive.encoder->GetEncoderRotations()) : config.drivetrain->GetConfig().rightdrive.encoder->GetEncoderotations();

		if (wheelRotations) {
			currentRotationsLeft /= config.gearBoxReduction;
			currentRotationsRight /= config.gearBoxReduction;
		}

		return ((currentRotationsLeft + currentRotationsRight)/2);
	}

	double ShipControl::currentLocation_M(Config &config) {
		double currentRotationsLeft = config.invertLeftENC ? inverse(config.drivetrain->GetConfig().leftDrive.encoder->GetEncoderRotations()) : config.drivetrain->GetConfig().leftDrive.encoder->GetEncoderRotations();
		double currentRotationsRight = config.invertRightENC ? inverse(config.drivetrain->GetConfig().rightDrive.encoder->GetEncoderRotations()) : config.drivetrain->GetConfig().rightDrive.encoder->GetEncoderRotations();
	
		currentRotationsLeft /= config.gearBoxReduction;
		currentRotationsRight /= config.gearBoxReduction;

		double currentMetersLeft = currentRotationsLeft * (A_PI * config.wheelDiameter);
		double currentMetersRight = currentRotationsRight * (A_PI * config.wheelDiameter);

		return ((currentMetersLeft + currentMetersRight)/2);
	}

	double ShipControl::gyroFollow(lLine line, double dt, Config &config) {
		double gyroGoal = line.angle;
		double output = gyroGoal - config.drivetrain->GetConfig().gyro->GetAngle();
		output /= 360;

		valueLimit(output, config.maxTurnSpeed, config.dynamicLimits);
		return output;
	}

	bool ShipControl::turn2angle(double angle, double dt, Config &config, bool noPID) {
		double angleSpeed = noPID ? config.maxTurnSpeed : internalPID(dt, angle, config.drivetrain->GetConfig().gyro->GetAngle(), config, true);
		double leftSpeed = 0, rightSpeed = 0;

		valueLimit(angleSpeed, config.maxTurnSpeed, config.dynamicLimits);
		leftSpeed += angleSpeed;
		rightSpeed -= angleSpeed;

		config.drivetrain->Set(leftSpeed, rightSpeed);

		if (abs(config.drivetrain->GetConfig().gyro->GetAngle() > abs(angle - _anglePrc) && abs(config.drivetrain->GetConfig().gyro->GetAngle(), config, true))) {
			config.drivetrain->Set(0,0);
			return true;
		} else {
			return false;
		}
	}

	bool ShipControl::driveToTarget(lPath *path, int line, bool reverse, double dt, Config &config) {
		double rotations2Target = rotationsToTarget(path->lines[line], config, true);
		double currentRotations = currentLocation_R(config, true);
		double gyroVal = config.drivetrain->GetConfig().gyro->GetAngle();

		if (currentRotations > rotations2Target-_bar) {
			config.drivetrain->Set(0,0);
			return true;
		} else {
			double leftSpeed = config.maxSpeed;
			double rightSpeed = config.maxSpeed;
			double turnSpeed = gyroFollow(path->lines[line], dt, config);
			valueLimit(gyroVal, config.maxTurnSpeed, config.dynamicLimits);

			leftSpeed += turnSpeed;
			rightSpeed -= turnSpeed;

			leftSpeed = reverse ? inverse(leftSpeed) : leftSpeed;
			rightSpeed = reverse ? inverse(rightSpeed) : rightSpeed;

			config.drivetrain->Set(leftSpeed, rightSpeed);
			return false;
		}
	}
}