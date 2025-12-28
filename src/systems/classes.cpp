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

Intake::Intake(pros::Motor* intakeMotor_, pros::Motor* hoodMotor_, pros::adi::Pneumatics intakeTray_, pros::adi::Pneumatics hoodTilter_, pros::Optical ringColorSensor_)
    : intakeMotor(intakeMotor_), hoodMotor(hoodMotor_), intakeTray(intakeTray_), hoodTilter(hoodTilter_), ringColorSensor(ringColorSensor_), state(Intake::STOP), oldColor(pros::Color::green), enableSort(true) {ringColorSensor.set_integration_time(10); ringColorSensor.set_led_pwm(100);}

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

void Intake::ScoreMid() {
    setState(Intake::SCORE_MID);
}

void Intake::ScoreMidSlow() {
    setState(Intake::SCORE_MID_SLOW);
}

void Intake::ScoreBottom() {
    setState(Intake::SCORE_BOTTOM);
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
            intakeTray.retract();
            //hoodTilter.retract();
            intakeMotor->brake();
            hoodMotor->brake();
            break;
        case IN:
            intakeTray.retract();
            //hoodTilter.retract();
            intakeMotor->move(intakeSpeed);
            pros::delay(50);
            if (intakeMotor->get_actual_velocity()==0) {
                intakeMotor->move(-127);
                pros::delay(50);
            }
            break;
        case OUT:
            intakeTray.retract();
            //hoodTilter.retract();
            intakeMotor->move(-intakeSpeed);
            break;
        case SCORE:
            intakeTray.retract();
            //hoodTilter.extend();
            intakeMotor->move(127);
            pros::delay(50);
            if (intakeMotor->get_actual_velocity()==0) {
                intakeMotor->move(-127);
                pros::delay(50);
            }
            hoodMotor->move(127);
            break;
        case SCORE_MID:
            intakeTray.extend();
            //hoodTilter.retract();
            intakeMotor->move(127);
            pros::delay(50);
            if (intakeMotor->get_actual_velocity()==0) {
                intakeMotor->move(-127);
                pros::delay(50);
            }
            hoodMotor->move((-127*0.70));
            break;
        case SCORE_MID_SLOW:
            intakeTray.extend();
            //hoodTilter.retract();
            intakeMotor->move((127*1.00));
            pros::delay(50);
            if (intakeMotor->get_actual_velocity()==0) {
                intakeMotor->move(-127);
                pros::delay(50);
            }
            hoodMotor->move((-127*0.41));
            break;
        case SCORE_BOTTOM:
            intakeMotor->move_velocity(-300);
            break;
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