#pragma once

#include "api.h"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/motor_group.hpp"
#include "pros/optical.hpp"
#include "systems/classes.hpp"
#include <cstddef>

inline pros::Motor intakemotor(20, pros::MotorGearset::blue);
inline pros::Motor hoodmotor(-11, pros::MotorGearset::blue);
inline pros::Distance topBallSensor(21);
inline pros::Optical blockColor(22);
inline pros::adi::Pneumatics intakeTray(1, false);
inline pros::adi::Pneumatics hoodLift(2, false);

inline Intake Intake(&intakemotor, &hoodmotor, intakeTray, hoodLift, blockColor);