#pragma once

#include "api.h"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/motor_group.hpp"
#include "pros/optical.hpp"
#include "systems/classes.hpp"
#include <cstddef>

inline pros::Motor intakemotor(-1, pros::MotorGearset::blue);
inline pros::Motor hoodmotor(-8, pros::MotorGearset::blue);
inline pros::Distance topBallSensor(0);
inline pros::Optical blockColor(0);
inline pros::adi::Pneumatics intakeTray(5, false);
inline pros::adi::Pneumatics hoodLift(-1, false);

inline Intake Intake(&intakemotor, &hoodmotor, intakeTray, hoodLift, blockColor);