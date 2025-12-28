#include "autos.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "systems/classes.hpp"
#include "systems/drive.hpp"
#include "systems/intake.hpp"
#include "systems/loader.hpp"
#include <sys/_intsup.h>

/**
* @brief Move the robot a relative distance forwards or backwards
*
* @param distance distance to be moved
* @param timeout the timeout duration for the movement
*/
void moveRelative(float distance, float maxSpeed, int timeout) {
    double headingRadians = chassis.getPose(true).theta;
    double startingX = chassis.getPose().x;
    double startingY = chassis.getPose().y;
    double deltaX = distance * sin(headingRadians);
    double deltaY = distance * cos(headingRadians);
    double newX = startingX + deltaX;
    double newY = startingY + deltaY;
    if (distance > 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=true, .maxSpeed=maxSpeed});
    }
    else if (distance < 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=false, .maxSpeed=maxSpeed});
    }
};

void relativeOdom(float xChange, float yChange, float maxSpeed, int timeout) {
    float currentX = chassis.getPose().x;
    float currentY = chassis.getPose().y;
    chassis.moveToPoint((currentX+xChange), (currentY+yChange), timeout);
}

void straightLine(float x, float y, float turnTimeout, float driveTimeout, lemlib::TurnToPointParams turnParams = {}, lemlib::MoveToPointParams driveParams = {}) {
    chassis.turnToPoint(x, y, turnTimeout, turnParams);
    chassis.waitUntilDone();
    chassis.moveToPoint(x, y, driveTimeout, driveParams);
}

void soloPleaseHit() {
    chassis.setPose(-48, -17.25, 180);
    chassis.moveToPoint(-48, -48, 750);
    Loader.extend();
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 500);
    chassis.waitUntilDone();
    Intake.In();
    chassis.moveToPoint(-58, -48, 500);
    chassis.waitUntilDone();
    chassis.tank((127*0.4), (127*0.4));
    pros::delay(550);
    chassis.tank(0, 0);
    chassis.moveToPoint(-28, -48, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(1000);
    Intake.Stop();
    Loader.retract();
    chassis.moveToPoint(-48, -48, 300);
    chassis.waitUntilDone();
    chassis.moveToPoint(-24, -24, 1000);
    Intake.In();
    // chassis.waitUntil(22);
    // Loader.extend();
    chassis.moveToPoint(-24, 28, 1250);
    // chassis.waitUntil(4);
    // Loader.retract();
    chassis.waitUntil(34);
    Loader.extend();
    chassis.waitUntilDone();
    chassis.turnToPoint(-7, 13, 500, {.forwards=false});
    chassis.waitUntilDone();
    chassis.moveToPoint(-7, 13, 650, {.forwards=false});
    Intake.Out();
    chassis.waitUntil(1);
    Intake.Stop();
    chassis.waitUntilDone();
    Intake.ScoreMid();
    pros::delay(1350);
    chassis.moveToPoint(-48, 54, 1000);
    Intake.Stop();
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 500);
    chassis.waitUntilDone();
    Intake.In();
    chassis.moveToPoint(-58, 54, 650);
    chassis.waitUntilDone();
    chassis.tank((127*0.75), (127*0.75));
    pros::delay(550);
    chassis.tank(0, 0);
    chassis.moveToPoint(-28, 54, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(1850);
    Intake.Stop();
    Loader.retract();
}

void Split7Left() {
    chassis.setPose(-48, 17, 90);
    chassis.moveToPoint(-24, 24, 750);
    Intake.In();
    chassis.waitUntil(18);
    Loader.extend();
    chassis.waitUntilDone();
    chassis.turnToPoint(-8, 8, 500, {.forwards=false});
    chassis.waitUntilDone();
    chassis.moveToPoint(-8, 8, 750, {.forwards=false});
    chassis.waitUntilDone();
    Intake.ScoreMid();
    pros::delay(1500);
    chassis.moveToPoint(-48, 51, 1000);
    chassis.waitUntil(4);
    Intake.Stop();
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 500);
    chassis.waitUntilDone();
    Intake.In();
    chassis.moveToPoint(-58, 51, 650);
    chassis.waitUntilDone();
    chassis.tank((127*0.5), (127*0.5));
    pros::delay(550);
    chassis.tank(0, 0);
    chassis.moveToPoint(-28, 51, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(1850);
    Intake.Stop();
    Loader.retract();
    chassis.moveToPoint(-48, 38, 1250);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 500);
    chassis.waitUntilDone();
    chassis.moveToPoint(-8, 38, 1000, {.forwards=false});
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 500);
    chassis.waitUntilDone();
}

void right9() {
    chassis.setPose(-48, -17, 90);
    chassis.moveToPoint(-24, -24, 750);
    Intake.In();
    DescoreArm.extend();
    // chassis.waitUntil(18);
    // Loader.extend();
    chassis.waitUntilDone();
    chassis.turnToPoint(-5, -48, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-6, -44, 1250);
    Loader.retract();
    chassis.waitUntilDone();
    Loader.extend();
    pros::delay(500);
    moveRelative(-16, 127, 750);
    chassis.waitUntil(12);
    Intake.Out();
    chassis.waitUntil(13);
    Intake.Stop();
    chassis.waitUntilDone();
    Loader.retract();
    chassis.turnToPoint(-48, -51, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-48, -51, 1250);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-28, -51, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(1500);
    Intake.In();
    Loader.extend();
    chassis.turnToHeading(270, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-58, -51, 1000);
    chassis.waitUntilDone();
    chassis.tank((127*0.5), (127*0.5));
    pros::delay(600);
    chassis.tank(0, 0);
    chassis.moveToPoint(-28, -51, 1250, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(1000);
    Intake.Stop();
    Loader.retract();
    DescoreArm.retract();
    
    
}

void skills() {

    Intake.In();
    chassis.tank(60,60);
    pros::delay(600);
    chassis.tank(60, 60);
    pros::delay(650);
    Loader.extend();
    pros::delay(1200);
    chassis.tank(-25, -25);
    pros::delay(1500);
    chassis.tank(0, 0);
    chassis.setPose((-48-15.5),18,0);
    Loader.retract();
    straightLine(-48, 36, 500, 750);
    chassis.waitUntilDone();
    straightLine(-24, 0, 500, 1000);
    chassis.waitUntilDone();
    Intake.In();
    straightLine(-14, 24, 500, 750);
    chassis.waitUntilDone();
    chassis.turnToHeading(315, 500);
    chassis.waitUntilDone();
    Intake.Stop();
    chassis.moveToPose(-12, 14, 315, 1250, {.forwards=false});
    chassis.waitUntilDone();
    Loader.extend();
    chassis.tank(-45, -45);
    pros::delay(350);
    chassis.tank(0, 0);
    chassis.turnToHeading(315, 500);
    Intake.ScoreMidSlow();
    moveRelative(0.5, 127, 250);
    pros::delay(4000);
    moveRelative(3, 127, 500);
    chassis.waitUntilDone();
    Intake.Stop();
    straightLine(-48, 51, 500, 1250);
    chassis.waitUntilDone();
    Intake.In();
    straightLine(-58, 51, 750, 750);
    chassis.waitUntilDone();
    chassis.tank(75, 75);
    pros::delay(1000);
    chassis.tank(0, 0);
    chassis.setPose(-58, 48, chassis.getPose().theta);
    straightLine(-36, 60, 500, 750, {.forwards=false}, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Stop();
    straightLine(45, 60, 500, 4000, {.forwards=false}, {.forwards=false});
    Loader.retract();
    chassis.waitUntilDone();
    straightLine(50, 43.5, 750, 1250, {.forwards=false}, {.forwards=false});
    chassis.waitUntilDone();
    straightLine(28, 43.5, 750, 750, {.forwards=false}, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(2000);
    Intake.Stop();
    Loader.extend();
    chassis.setPose(30.5,48,chassis.getPose().theta);
    straightLine(58, 48, 500, 1000);
    Intake.In();
    chassis.waitUntilDone();
    chassis.tank(75, 75);
    pros::delay(1000);
    chassis.tank(0, 0);
    chassis.setPose(58, 48, chassis.getPose().theta);
    straightLine(25, 48, 500, 1000, {.forwards=false}, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(2000);
    Intake.Stop();
    straightLine(36, 48, 500, 750);
    chassis.waitUntilDone();
    straightLine(46, -52, 750, 2500);
    chassis.waitUntilDone();
    Loader.extend();
    straightLine(58, -52, 750, 1000);
    Intake.In();
    chassis.waitUntilDone();
    chassis.tank(75, 75);
    pros::delay(1000);
    chassis.tank(0, 0);
    chassis.setPose(58, -48, chassis.getPose().theta);
    straightLine(36, -60, 500, 750, {.forwards=false}, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Stop();
    straightLine(-45, -60, 500, 4000, {.forwards=false}, {.forwards=false});
    Loader.retract();
    chassis.waitUntilDone();
    straightLine(-50, -48, 750, 1250, {.forwards=false}, {.forwards=false});
    chassis.waitUntilDone();
    straightLine(-28, -48, 750, 750, {.forwards=false}, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(2000);
    Intake.Stop();
    Loader.extend();
    chassis.setPose(-30.5,-48,chassis.getPose().theta);
    straightLine(-58, -48, 500, 1000);
    Intake.In();
    chassis.waitUntilDone();
    chassis.tank(75, 75);
    pros::delay(1000);
    chassis.tank(0, 0);
    chassis.setPose(-58, -48, chassis.getPose().theta);
    straightLine(-28, -48, 500, 1000, {.forwards=false}, {.forwards=false});
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 500);
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(2000);
    Intake.Stop();
    Loader.retract();
    straightLine(-36, -48, 500, 750);
    chassis.waitUntilDone();
    straightLine(-36, 0, 750, 1250);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 750);
    chassis.waitUntilDone();
    chassis.tank(127, 127);
    pros::delay(1250);
    chassis.tank(0, 0);



}

void pidTuning() {
     // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    // move 48" forwards
    chassis.moveToPoint(0, 48, 10000);
}