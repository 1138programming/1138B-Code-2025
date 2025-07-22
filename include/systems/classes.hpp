#pragma once
#include "api.h"
#include "LemLib/PID.hpp"
#include "pros/adi.hpp"
#include "pros/colors.hpp"
#include "pros/motors.h"
#include "pros/optical.hpp"
#include <string>

// class definitions
class Intake {
    
    public:
        Intake(pros::Motor intakeMotor, pros::Motor indexerMotor, pros::Distance ballDetector, pros::Distance topBallDetector, pros::adi::Pneumatics intakeTilter, pros::Optical ringColorSensor);
        enum States {
            IN,
            OUT,
            STOP,
            SCORE_UP,
            SCORE_DOWN
        };
        void setSpeed(int speed); // set the speed for the intake
        void setSortColor(pros::Color setColor);
        void colorSort();
        void updateState();
        States getState();
        void setState(States newState);
        bool enableSort;
        pros::Color currentRingColor;
        void Advance();
        void Retreat();
        void In();
        void Out();
        void Stop();
        void ScoreUp();
        void ScoreDown();
        std::string getSortColor();

    private:
        pros::Optical ringColorSensor;
        pros::Distance ballDetector;
        pros::Distance topBallDetector;
        pros::adi::Pneumatics intakeTilter;
        pros::Motor intakeMotor;
        pros::Motor indexerMotor;
        pros::Color setColor;
        pros::Color oldColor;
        int intakeSpeed;
        bool sortNeeded;
        States state;
        
        
};