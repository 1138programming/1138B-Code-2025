#pragma once

#include "api.h"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/motor_group.hpp"
#include "pros/optical.hpp"
#include "systems/classes.hpp"
#include <cstddef>

inline pros::MotorGroup intakemotors({11, 12}, pros::MotorGearset::blue);
inline pros::Distance topBallSensor(21);
inline pros::Optical blockColor(22);
inline pros::adi::Pneumatics intakeGate(1, false);
inline pros::adi::Pneumatics intakeLift(2, true);

inline Intake Intake(&intakemotors, intakeGate, intakeLift, blockColor);