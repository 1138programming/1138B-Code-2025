#pragma once
#include "api.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"

// motors



inline pros::MotorGroup left_motors({-11, -13, 14}, pros::MotorGearset::blue);

inline pros::MotorGroup right_motors({16, 18, -17}, pros::MotorGearset::blue);

// sensors

inline pros::IMU imu(10);
inline pros::Rotation horzTracking(15);
inline pros::Rotation vertTracking(-19);
inline pros::Distance leftDistance(12);
inline pros::Distance rightDistance(20);
inline pros::Distance frontDistance(21);

inline lemlib::TrackingWheel vertTracker(&vertTracking, 2.05, 0);
inline lemlib::TrackingWheel horzTracker(&horzTracking, 2.05, 0);
// LEMLIB

inline double trackWidth = 10.25;
inline double WheelSize = lemlib::Omniwheel::NEW_325;
inline int DriveRPM = 450;
inline int HorzDrift = 24;

// drivetrain settings

inline lemlib::Drivetrain drivetrain(
    &left_motors, // left motor group
    &right_motors, // right motor group
    trackWidth, // set the trackWidth variable to our LemLib track width
    WheelSize, // set the WheelSize variable to our LemLib wheel size
    DriveRPM, // set the DriveRPM variable to our LemLib RPM
    HorzDrift // set the HorzDrift variable to our horizontal drift tracking in LemLib
);

// tracking wheels


// odom settings

inline lemlib::OdomSensors OdomSensors(&vertTracker, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horzTracker, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// PIDs

// Lateral PID
inline lemlib::ControllerSettings lateral_controller(
    13,   // kP 
    0,   // kI
    80,   // kD
    0,   // anti-windup
    1,   // small error (inches)
    100,    // small error timeout (ms)
    3,   // large error (inches)
    500,   // large error timeout (ms)
    0.0    // slew (accel only; leave 0 for now)
);

// Angular PID

// Angular PID
inline lemlib::ControllerSettings angular_controller(
    3.6,   // kP  
    0.0,   // kI
    30.0,  // kD 
    0.0,   // anti-windup
    2,   // small error (degrees)
    75,    // small error timeout (ms)
    3.5,   // large error (degrees)
    250,   // large error timeout (ms)
    0.0    // slew
);                                  

// Chassis Constructor

inline lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        OdomSensors // odometry sensors
);