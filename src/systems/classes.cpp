#include "systems/classes.hpp"
#include "intake.hpp"
#include "pros/adi.hpp"
#include "pros/colors.hpp"
#include "pros/distance.hpp"
#include "pros/motors.h"
#include "pros/optical.hpp"
#include "pros/rtos.hpp"
#include "systems/controlscheme.hpp"
#include <string>


//intake

Intake::Intake(pros::MotorGroup* intakeMotors_, pros::adi::Pneumatics intakeGate_, pros::adi::Pneumatics intakeTilter_, pros::Optical ringColorSensor_)
    : intakeMotors(intakeMotors_), intakeGate(intakeGate_), intakeTilter(intakeTilter_), ringColorSensor(ringColorSensor_), state(Intake::STOP), oldColor(pros::Color::green), enableSort(true) {ringColorSensor.set_integration_time(10); ringColorSensor.set_led_pwm(100);}

void Intake::setState(States newState) {
    state = newState;
}

void Intake::Out() {
    setState(Intake::OUT);
}

void Intake::In() {
    setState(Intake::IN);
}

void Intake::Score() {
    setState(Intake::SCORE);
}

void Intake::ScoreBottom() {
    setState(Intake::SCORE_BOTTOM);
}

void Intake::ToggleHeight() {
    intakeTilter.toggle();
}

void Intake::Stop() {
    setState(Intake::STOP);
}

void Intake::setSortColor(pros::Color setColor_) {
    setColor = setColor_;
}

void Intake::colorSort() {
    if ((ringColorSensor.get_raw().blue > 350 && ringColorSensor.get_raw().red < 600) && ringColorSensor.get_proximity() > 200) {
        currentRingColor = pros::Color::blue;
    }
    else if ((ringColorSensor.get_raw().red > 400 && ringColorSensor.get_raw().blue < 300) && ringColorSensor.get_proximity() > 200) {
        currentRingColor = pros::Color::red;
    }
    else {
        currentRingColor = pros::Color::green;
    };
    if (enableSort && ((currentRingColor != setColor) && (currentRingColor != pros::Color::green)) && (oldColor != currentRingColor)) {
        sortNeeded = true;
        oldColor = currentRingColor;
    }
    else {
        sortNeeded = false;
    }
    oldColor = currentRingColor;
}
void Intake::setSpeed(int speed) {
    Intake::intakeSpeed = speed;
}

void Intake::updateState() {
    switch (state) {
        case STOP:
            intakeGate.extend();
            intakeMotors->brake();
            // indexerMotor.brake();
            break;
        case IN:
            intakeGate.extend();
            intakeMotors->move(intakeSpeed);
            break;
        case OUT:
            intakeGate.extend();
            intakeMotors->move(-intakeSpeed);
            break;
        case SCORE:
            intakeGate.retract();
            // pros::delay(250);
            intakeMotors->move(127);
            break;
        case SCORE_BOTTOM:
            intakeMotors->move_velocity(-300);
    }
}


std::string Intake::getSortColor() {
    switch (setColor) {
        case pros::Color::red:
            return "Red";
            break;
        case pros::Color::blue:
            return "Blue";
            break;
        default:
            return "";
            break;
    }
}