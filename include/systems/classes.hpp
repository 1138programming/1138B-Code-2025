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
        Intake(pros::Motor* intakeMotor, pros::Motor* hoodMotor, pros::adi::Pneumatics intakeTray, pros::adi::Pneumatics hoodTilter, pros::Optical ringColorSensor);
        enum States {
            IN,
            OUT,
            STOP,
            SCORE,
            SCORE_MID,
            SCORE_MID_SLOW,
            SCORE_BOTTOM
        };
        void setSpeed(int speed); // set the speed for the intake
        void setSortColor(pros::Color setColor);
        void colorSort();
        void updateState();
        States getState();
        void setState(States newState);
        bool enableSort;
        pros::Color currentRingColor;
        void In();
        void Out();
        void Stop();
        void Score();
        void ScoreMid();
        void ScoreMidSlow();
        void ScoreBottom();
        std::string getSortColor();

    private:
        pros::Optical ringColorSensor;
        pros::adi::Pneumatics intakeTray;
        pros::adi::Pneumatics hoodTilter;
        pros::Motor* intakeMotor;
        pros::Motor* hoodMotor;
        pros::Color setColor;
        pros::Color oldColor;
        int intakeSpeed;
        bool sortNeeded;
        States state;
        
        
};