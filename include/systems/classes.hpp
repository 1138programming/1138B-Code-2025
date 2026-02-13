#pragma once
#include "api.h"
#include "LemLib/PID.hpp"
#include "pros/adi.hpp"
#include "pros/colors.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include <string>

// class definitions
class Intake {
public:

    // Constructor
    Intake(pros::Motor* intakeMotor_,
           pros::Motor* hoodMotor_,
           pros::adi::Pneumatics intakeTray_,
           pros::adi::Pneumatics hoodTilter_,
           pros::Optical ringColorSensor_);

    // ====== Main periodic function ======
    void Updater();

    // ====== Control commands (call on button edge) ======
    void In();
    void MidIn();
    void Out();
    void Score();
    void ScoreMid();
    void ScoreMidSlow();
    void ScoreBottom();
    void Stop();

    // ====== Config ======
    void setSpeed(int speed);
    void setSortColor(pros::Color setColor_);
    std::string getSortColor();

private:

    // ====== Hardware ======
    pros::Motor* intakeMotor;
    pros::Motor* hoodMotor;
    pros::adi::Pneumatics intakeTray;
    pros::adi::Pneumatics hoodTilter;
    pros::Optical ringColorSensor;

    // ====== Commanded outputs ======
    int intakeCmd = 0;
    int hoodCmd = 0;
    bool trayExtended = false;
    int intakeSpeed = 127;

    // ====== Anti-jam ======
    void antiJam();
    uint32_t cmdSetTime = 0;
    uint32_t jamStartTime = 0;
    bool jamActive = false;

    // ====== Color sorting ======
    void colorSort();
    pros::Color setColor{pros::Color::red};
    pros::Color currentRingColor{pros::Color::green};
    pros::Color oldColor{pros::Color::green};
    bool enableSort = true;
    bool sortNeeded = false;
};