#pragma once

#include "api.h"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/motor_group.hpp"
#include "pros/optical.hpp"
#include "systems/classes.hpp"
#include <cstddef>

inline pros::Motor intakemotor(-11, pros::MotorGearset::blue);
inline pros::Motor hoodmotor(12, pros::MotorGearset::blue);
inline pros::Distance topBallSensor(21);
inline pros::Optical blockColor(22);
inline pros::adi::Pneumatics intakeTray(5, false);
inline pros::adi::Pneumatics intakeLift(3, true);
inline pros::adi::Pneumatics hoodLift(8, false);

inline Intake Intake(&intakemotor, &hoodmotor, intakeTray, intakeLift, hoodLift, blockColor);