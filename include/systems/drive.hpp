#pragma once
#include "api.h"
#include "lemlib/api.hpp"
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"

// motors



inline pros::MotorGroup left_motors({-13, -11, 12}, pros::MotorGearset::blue);

inline pros::MotorGroup right_motors({18, 20, -19}, pros::MotorGearset::blue);

// sensors

inline pros::IMU imu(10);
inline pros::Rotation horzTracking(17);
inline pros::Rotation vertTracking(-16);

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

inline lemlib::ControllerSettings lateral_controller(9.5, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              35, // derivative gain (kD)
                                              0, // anti windup
                                              2, // small error range, in inches
                                              50, // small error range timeout, in milliseconds
                                              5, // large error range, in inches
                                              125, // large error range timeout, in milliseconds
                                              40 // maximum acceleration (slew)
);

// Angular PID

inline lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0.0, // integral gain (kI)
                                              15, // derivative gain (kD)
                                              0, // anti windup
                                              3, // small error range, in inches
                                              50, // small error range timeout, in milliseconds
                                              5, // large error range, in inches
                                              150, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// Chassis Constructor

inline lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        OdomSensors // odometry sensors
);