#include "systems/classes.hpp"
#include "pros/adi.hpp"
#include "pros/colors.hpp"
#include "pros/distance.hpp"
#include "pros/motors.h"
#include "pros/optical.hpp"
#include "pros/rtos.hpp"
#include "systems/controlscheme.hpp"
#include <string>


//intake

Intake::Intake(pros::Motor intakeMotor_, pros::Motor indexerMotor_, pros::Distance ballDetector_, pros::Distance topBallDetector_, pros::adi::Pneumatics intakeTilter_, pros::Optical ringColorSensor_)
    : intakeMotor(intakeMotor_), indexerMotor(indexerMotor_), ballDetector(ballDetector_), topBallDetector(topBallDetector_), intakeTilter(intakeTilter_), ringColorSensor(ringColorSensor_), state(Intake::STOP), oldColor(pros::Color::green), enableSort(true) {ringColorSensor.set_integration_time(10); ringColorSensor.set_led_pwm(100); indexerMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);}

void Intake::setState(States newState) {
    state = newState;
}

void Intake::Out() {
    setState(Intake::OUT);
}

void Intake::In() {
    setState(Intake::IN);
}

void Intake::ScoreUp() {
    setState(Intake::SCORE_UP);
}

void Intake::ScoreDown() {
    setState(Intake::SCORE_DOWN);
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
            intakeMotor.brake();
            // indexerMotor.brake();
            break;
        case IN:
            intakeMotor.move(intakeSpeed);
            if (ballDetector.get() < 130 && !(topBallDetector.get() < 130)) {
                Advance();
            }
            // if (sortNeeded) {
            //     sortNeeded = false;
            //     pros::delay(150);
            //     intakeMotor.move(-intakeSpeed);
            //     pros::delay(100);
            // };
            break;
        case OUT:
            intakeMotor.move(-intakeSpeed);
            Retreat();
            break;
        case SCORE_UP:
            intakeTilter.retract();
            // pros::delay(250);
            intakeMotor.move(127);
            indexerMotor.move(127);
            break;
        case SCORE_DOWN:
            intakeTilter.extend();
            // pros::delay(250);
            intakeMotor.move(127);
            indexerMotor.move(127);
    }
}

void Intake::Advance() {
    indexerMotor.move(100);
    pros::delay(20);
    indexerMotor.brake();
}

void Intake::Retreat() {
    indexerMotor.move(-intakeSpeed);
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
