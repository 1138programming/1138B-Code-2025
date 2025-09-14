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
        Intake(pros::MotorGroup* intakeMotors, pros::adi::Pneumatics intakeGate, pros::adi::Pneumatics intakeTilter, pros::Optical ringColorSensor);
        enum States {
            IN,
            OUT,
            STOP,
            SCORE,
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
        void ToggleHeight();
        void ScoreBottom();
        std::string getSortColor();

    private:
        pros::Optical ringColorSensor;
        pros::adi::Pneumatics intakeGate;
        pros::adi::Pneumatics intakeTilter;
        pros::MotorGroup* intakeMotors;
        pros::Color setColor;
        pros::Color oldColor;
        int intakeSpeed;
        bool sortNeeded;
        States state;
        
        
};