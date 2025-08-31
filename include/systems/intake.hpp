#pragma once

#include "api.h"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/optical.hpp"
#include "systems/classes.hpp"

inline pros::Motor intake(11, pros::MotorGearset::blue);
inline pros::Motor indexer(-4, pros::MotorGearset::blue, pros::MotorEncoderUnits::degrees);
inline pros::Distance ballSensor(2);
inline pros::Distance topBallSensor(21);
inline pros::Optical ringColor(22);
inline pros::adi::Pneumatics intakeLift(8, false);

inline Intake Intake(intake, indexer, ballSensor, topBallSensor, intakeLift, ringColor);