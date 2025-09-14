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
        Intake(pros::MotorGroup* intakeMotors, pros::Distance ballDetector, pros::Distance topBallDetector, pros::adi::Pneumatics intakeTilter, pros::Optical ringColorSensor);
        enum States {
            IN,
            OUT,
            STOP,
            SCORE_UP,
            SCORE_DOWN,
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
        void ScoreUp();
        void ScoreDown();
        void ScoreBottom();
        std::string getSortColor();

    private:
        pros::Optical ringColorSensor;
        pros::Distance ballDetector;
        pros::Distance topBallDetector;
        pros::adi::Pneumatics intakeTilter;
        pros::MotorGroup* intakeMotors;
        pros::Color setColor;
        pros::Color oldColor;
        int intakeSpeed;
        bool sortNeeded;
        States state;
        
        
};

class Loader {

    public:
        void deploy();
        void retract();
        void toggle();
        Loader(pros::adi::Pneumatics loaderPiston);

    private:
        pros::adi::Pneumatics loaderPiston;
};