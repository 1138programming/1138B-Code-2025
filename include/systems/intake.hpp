#pragma once

#include "api.h"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/optical.hpp"
#include "systems/classes.hpp"

inline pros::Motor intake(2, pros::MotorGearset::blue);
inline pros::Motor indexer(10, pros::MotorGearset::blue, pros::MotorEncoderUnits::degrees);
inline pros::Distance ballSensor(1);
inline pros::Distance topBallSensor(2);
inline pros::Optical ringColor(22);
inline pros::adi::Pneumatics intakeLift(4, false);

inline Intake Intake(intake, indexer, ballSensor, topBallSensor, intakeLift, ringColor);