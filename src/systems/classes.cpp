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
    : intakeMotor(intakeMotor_), hoodMotor(hoodMotor_), intakeTray(intakeTray_), hoodTilter(hoodTilter_), ringColorSensor(ringColorSensor_), oldColor(pros::Color::green), enableSort(true) {ringColorSensor.set_integration_time(10); ringColorSensor.set_led_pwm(100);}

void Intake::In() {
    intakeCmd = intakeSpeed;
    hoodCmd = -127 * 0.1;
    trayExtended = false;
    cmdSetTime = pros::millis();
}

void Intake::MidIn() {
    intakeCmd = 0;
    hoodCmd = 127 * 0.5;
    trayExtended = true;
    cmdSetTime = pros::millis();
}

void Intake::Out() {
    intakeCmd = -intakeSpeed;
    hoodCmd = 0;
    trayExtended = false;
    cmdSetTime = pros::millis();
}

void Intake::Score() {
    intakeCmd = 127;
    hoodCmd = 127;
    trayExtended = false;
    cmdSetTime = pros::millis();
}

void Intake::ScoreMid() {
    intakeCmd = 127;
    hoodCmd = -127 * 0.7;
    trayExtended = true;
    cmdSetTime = pros::millis();
}

void Intake::ScoreMidSlow() {
    intakeCmd = 127;
    hoodCmd = -127 * 0.41;
    trayExtended = true;
    cmdSetTime = pros::millis();
}

void Intake::ScoreBottom() {
    intakeCmd = -127 * 0.5;
    hoodCmd = 0;
    trayExtended = false;
    cmdSetTime = pros::millis();
}

void Intake::Stop() {
    intakeCmd = 0;
    hoodCmd = 0;
    trayExtended = false;
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

void Intake::antiJam() {

    uint32_t now = pros::millis();

    // Only anti-jam if running forward
    if (intakeCmd <= 0) return;

    // Let motor spin up before checking
    if (now - cmdSetTime < 200) return;

    // If currently reversing to clear jam
    if (jamActive) {
        if (now - jamStartTime > 80) {
            jamActive = false;  // stop reversing
        } else {
            intakeMotor->move(-127);
            return;
        }
    }

    // Detect stall (use threshold, not == 0)
    if (std::abs(intakeMotor->get_actual_velocity()) < 5) {
        jamActive = true;
        jamStartTime = now;
        intakeMotor->move(-127);
    }
}

void Intake::Updater() {

    //colorSort();   // your existing logic
    antiJam();     // non-blocking jam control

    // Apply pneumatics
    if (trayExtended)
        intakeTray.extend();
    else
        intakeTray.retract();

    // If antiJam isn't temporarily overriding, apply normal command
    if (!jamActive)
        intakeMotor->move(intakeCmd);

    hoodMotor->move(hoodCmd);
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