#include "autos.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "pros/rtos.hpp"
#include "systems/classes.hpp"
#include "systems/drive.hpp"
#include "systems/distanceReset.hpp"
#include "systems/distanceSensors.hpp"
#include "systems/intake.hpp"
#include "systems/loader.hpp"
#include <sys/_intsup.h>

/**
* @brief Move the robot a relative distance forwards or backwards
*
* @param distance distance to be moved
* @param timeout the timeout duration for the movement
*/
void moveRelative(float distance, float maxSpeed, float minSpeed, int timeout) {
    double headingRadians = chassis.getPose(true).theta;
    double startingX = chassis.getPose().x;
    double startingY = chassis.getPose().y;
    double deltaX = distance * sin(headingRadians);
    double deltaY = distance * cos(headingRadians);
    double newX = startingX + deltaX;
    double newY = startingY + deltaY;
    if (distance > 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=true, .maxSpeed=maxSpeed, .minSpeed=minSpeed});
    }
    else if (distance < 0) {
        chassis.moveToPoint(newX, newY, timeout, {.forwards=false, .maxSpeed=maxSpeed, .minSpeed=minSpeed});
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

void wiggle(int wiggleTime) {
    int wiggleCount = wiggleTime/200;
    for (int i = 0; i<wiggleCount; i++) {
        chassis.tank(-10, 75);
        pros::delay(100);
        chassis.tank(75, -10);
        pros::delay(100);
        chassis.tank(0, 0);
    }
}


void soloPleaseHit() {
    chassis.setPose(-47.5, 0, 0);
    Intake.In();
    chassis.moveToPoint(-47.5, 6, 1000, {.minSpeed=127});
    chassis.waitUntilDone();
    chassis.moveToPoint(-47.5, -48, 1500, {.forwards=false});
    chassis.waitUntilDone();
    Loader.extend();
    chassis.turnToHeading(270, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-58, -48, 1000, {.minSpeed=50});
    chassis.waitUntilDone();
    chassis.tank(25, 25);
    pros::delay(450);
    chassis.tank(0, 0);
    chassis.moveToPoint(-30, -48, 1500, {.forwards=false, .minSpeed=75});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(1250);
    Intake.Stop();
    Loader.retract();
    moveRelative(6, 127, 75, 750);
    chassis.turnToPoint(-24, -24, 750, {.minSpeed=50});
    chassis.waitUntilDone();
    chassis.moveToPoint(-24, -24, 1250, {.minSpeed=20, .earlyExitRange=12});
    Intake.In();
    chassis.waitUntil(16);
    Loader.extend();
    chassis.moveToPoint(-24, 24, 1000, {.minSpeed=30});
    chassis.waitUntil(14);
    Loader.retract();
    chassis.waitUntil(42);
    Loader.extend();
    chassis.waitUntilDone();
    // chassis.moveToPose(-13, 13, 315, 1500, {.forwards=false, .horizontalDrift=32});
    chassis.turnToPoint(-12, 12, 750, {.forwards=false, .minSpeed=30});
    chassis.waitUntilDone();
    chassis.moveToPoint(-12, 12, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Intake.ScoreMid();
    pros::delay(1000);
    chassis.moveToPoint(-47, 47, 1250, {.minSpeed=50});
    Intake.MidIn();
    chassis.waitUntil(6);
    Intake.Stop();
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 750);
    chassis.waitUntilDone();
    Intake.In();
    chassis.moveToPoint(-58, 47, 750, {.minSpeed=50});
    chassis.waitUntilDone();
    chassis.tank(25, 25);
    pros::delay(450);
    chassis.tank(0, 0);
    chassis.moveToPoint(-30, 47, 1500, {.forwards=false, .minSpeed=75});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(1250);
    // moveRelative(6, 127, 1250);
    // chassis.waitUntilDone();
    Loader.retract();
    Intake.Stop();
}

void Split7Left() {
    chassis.setPose(-48, 17, 90);
    chassis.moveToPoint(-24, 24, 1750);
    Intake.In();
    chassis.waitUntil(18);
    Loader.extend();
    chassis.waitUntilDone();
    chassis.turnToPoint(-8, 8, 1500, {.forwards=false});
    chassis.waitUntilDone();
    chassis.moveToPoint(-8, 8, 1750, {.forwards=false});
    chassis.waitUntilDone();
    Intake.ScoreMid();
    pros::delay(1500);
    chassis.moveToPoint(-48, 51, 2000);
    chassis.waitUntil(4);
    Intake.Stop();
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1500);
    chassis.waitUntilDone();
    Intake.In();
    chassis.moveToPoint(-58, 51, 1650);
    chassis.waitUntilDone();
    chassis.tank(75, 75);
    pros::delay(500);
    chassis.tank(0, 0);
    chassis.moveToPoint(-25, 51, 2000, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(1850);
    Intake.Stop();
    Loader.retract();
    chassis.moveToPoint(-48, 36, 2250);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 500);
    chassis.waitUntilDone();
    chassis.moveToPoint(-10, 36, 1000, {.forwards=false});
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 500);
    chassis.waitUntilDone();
}

void Split9Left() {
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
    straightLine(-24, 24, 500, 1000);
    Intake.Stop();
    chassis.waitUntilDone();
    Loader.retract();
    chassis.turnToPoint(-5, 48, 750);
    Intake.In();
    chassis.waitUntilDone();
    chassis.moveToPoint(7, 44, 1250);
    chassis.waitUntilDone();
    Loader.extend();
    pros::delay(500);
    moveRelative(-24, 127, 0, 1250);
    chassis.waitUntilDone();
    straightLine(-48, 51, 750,1250);
    chassis.waitUntil(4);
    Intake.Stop();
    Loader.extend();
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 500);
    chassis.waitUntilDone();
    Intake.In();
    chassis.moveToPoint(-58, 51, 650);
    chassis.waitUntilDone();
    chassis.tank(75, 75);
    pros::delay(500);
    chassis.tank(0, 0);
    chassis.moveToPoint(-25, 51, 1000, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(1850);
    Intake.Stop();
    Loader.retract();
    chassis.moveToPoint(-48, 36, 1250);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 500);
    chassis.waitUntilDone();
    chassis.moveToPoint(-10, 36, 1000, {.forwards=false});
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 500);
    chassis.waitUntilDone();
}

void right9() {
    chassis.setPose(-48, -17, 90);
    chassis.moveToPoint(-24, -24, 750);
    Intake.In();
    DescoreArm.extend();
    chassis.waitUntil(18);
    Loader.extend();
    chassis.waitUntilDone();
    straightLine(-9, -32, 500, 1000);
    Loader.retract();
    chassis.waitUntilDone();
    straightLine(-6, -48, 750, 1000);
    chassis.waitUntil(8);
    Loader.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(-24, -24, 1250, {.forwards=false});
    chassis.waitUntil(12);
    chassis.waitUntilDone();
    Loader.retract();
    chassis.turnToPoint(-48, -52, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-48, -52, 1500);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 750);
    chassis.waitUntilDone();
    chassis.moveToPoint(-28, -52, 1500, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(1500);
    Intake.Stop();
    Loader.extend();
    straightLine(-58, -52, 500, 1000);
    Intake.In();
    chassis.waitUntilDone();
    chassis.tank(75, 75);
    pros::delay(300);
    chassis.tank(0, 0);
    straightLine(-28, -52, 500, 1500, {.forwards=false}, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(1000);
    Intake.Stop();
    Loader.retract();
    DescoreArm.retract();
    
    
}

void right7() {
    chassis.setPose(-48, -17, 90);
    Intake.In();
    chassis.moveToPoint(-24, -24, 2500);
    chassis.waitUntil(10);
    Loader.extend();
    chassis.waitUntilDone();
    straightLine(-50, -48, 1250, 2500);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1500);
    chassis.waitUntilDone();
    chassis.tank(60, 60);
    pros::delay(1000);
    chassis.tank(0, 0);
    chassis.moveToPoint(-30, -49, 2500, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(2500);
    Intake.Stop();
    chassis.moveToPoint(-42, -49, 1500);
    chassis.waitUntilDone();
    straightLine(-30, -59, 1000, 2000, {.forwards=false}, {.forwards=false});
    chassis.waitUntilDone();
    straightLine(-12, -59, 1000, 3500, {.forwards=false}, {.forwards=false, .maxSpeed=127});
    chassis.waitUntilDone();
    chassis.turnToHeading(315, 1500, {.maxSpeed=60});
    chassis.waitUntilDone();
}

void left7() {
    chassis.setPose(-48, 17, 90);
    Intake.In();
    chassis.moveToPoint(-24, 24, 2500);
    chassis.waitUntil(12);
    Loader.extend();
    chassis.waitUntilDone();
    straightLine(-50, 47, 1250, 2500, {}, {.minSpeed=10,.earlyExitRange=1});
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1500);
    chassis.waitUntilDone();
    chassis.moveToPoint(-60, 47, 2500, {.minSpeed=40});
    chassis.waitUntilDone();
    chassis.tank(25, 25);
    pros::delay(500);
    chassis.tank(0, 0);
    chassis.moveToPoint(-30, 47, 2500, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(2000);
    Intake.Stop();
    chassis.moveToPoint(-42, 47, 1500);
    chassis.waitUntilDone();
    straightLine(-30, 37, 500, 2500, {.forwards=false}, {.forwards=false, .minSpeed=10, .earlyExitRange=2});
    chassis.waitUntilDone();
    straightLine(-11, 37, 1000, 5000, {.forwards=false}, {.forwards=false, .maxSpeed=100});
    chassis.waitUntilDone();
    chassis.turnToHeading(305, 5000, {.maxSpeed=60});
    chassis.waitUntilDone();
}

void left7splitWing() {
    chassis.setPose(-48, 16, 90);
    Intake.In();
    chassis.moveToPoint(-24, 24, 2500);
    chassis.waitUntil(10);
    Loader.extend();
    chassis.waitUntilDone();
    straightLine(-11, 11, 1500, 2500, {.forwards=false}, {.forwards=false});
    chassis.waitUntilDone();
    Intake.ScoreMid();
    pros::delay(1500);
    Intake.Stop();
    chassis.moveToPoint(-48, 45, 2500);
    chassis.waitUntil(4);
    Intake.Stop();
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1500);
    Loader.extend();
    chassis.waitUntilDone();
    Intake.In();
    chassis.tank(30, 30);
    pros::delay(1350);
    chassis.moveToPoint(-30, 45, 1500, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(1000);
    chassis.moveToPoint(-42, 45, 1500);
    Intake.Stop();
    chassis.waitUntilDone();
    straightLine(-30, 35, 1500, 2500, {.forwards=false}, {.forwards=false});
    chassis.waitUntilDone();
    straightLine(-12, 35, 1500, 2500, {.forwards=false}, {.forwards=false, .maxSpeed=60});
    chassis.waitUntilDone();
    chassis.turnToHeading(330, 1500, {.maxSpeed=60});
    chassis.waitUntilDone();

}

void skills() {
    chassis.setPose(0,0,0);
    DescoreArm.extend();
    Intake.In();
    chassis.tank(65,65);;
    pros::delay(1000);
    Loader.extend();
    pros::delay(500);
    while (frontDistance.get_distance() > 1100) {pros::delay(1);}
    DescoreArm.retract();
    chassis.tank(0, 0);
    chassis.turnToHeading(0, 750);
    resetRobotPos(leftDistance, "negative_x");
    resetRobotPos(frontDistance, "positive_y");
    Loader.retract();
    chassis.turnToPoint(-28, 30, 1500, {.minSpeed=50});
    chassis.waitUntilDone();
    chassis.moveToPoint(-28, 30, 3000, {.minSpeed=5, .earlyExitRange=3});
    chassis.waitUntilDone();
    chassis.turnToPoint(-11, 11, 1500, {.forwards=false});
    Loader.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(-11, 11, 4000, {.forwards=false, .maxSpeed=75});
    Intake.Out();
    chassis.waitUntil(4);
    Intake.Stop();
    chassis.waitUntilDone();
    Intake.ScoreMidSlow();
    pros::delay(5000);
    chassis.moveToPoint(-48, 50, 5000);
    Intake.MidIn();
    chassis.waitUntil(4);
    Intake.Stop();
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1500);
    chassis.waitUntilDone();
    resetRobotPos(frontDistance, "negative_x");
    resetRobotPos(rightDistance, "positive_y");
    Intake.In();
    chassis.moveToPoint(-54, 48, 2500, {.minSpeed=50, .earlyExitRange=2});
    chassis.waitUntilDone();
    chassis.moveToPoint(-60, 48, 2500, {.maxSpeed=40});
    chassis.waitUntilDone();
    // chassis.tank(50,50);
    // pros::delay(2000);
    // chassis.tank(0, 0);
    wiggle(2250);
    moveRelative(-10, 127, 80, 1250);
    chassis.waitUntilDone();
    Loader.retract();
    Intake.Stop();
    // chassis.moveToPoint(-36, 60, 3000, {.forwards=false, .minSpeed=5, .earlyExitRange=8});
    straightLine(-30, 58, 1500, 3000, {.forwards=false}, {.forwards=false, .minSpeed=50, .earlyExitRange=6});
    chassis.waitUntilDone();
    chassis.moveToPoint(36, 58, 5000, {.forwards=false, .minSpeed=75});
    chassis.waitUntilDone();
    // chassis.moveToPoint(48, 48, 5000, {.forwards=false});
    straightLine(48, 45, 1500, 3500, {.forwards=false, .minSpeed=20}, {.forwards=false});
    chassis.waitUntilDone();
    chassis.turnToPoint(30, 45, 1500, {.forwards=false});
    chassis.waitUntilDone();
    chassis.moveToPoint(31, 45, 2500, {.forwards=false, .minSpeed=75});
    chassis.waitUntilDone();
    chassis.tank(-127, -127);
    pros::delay(750);
    chassis.tank(0, 0);
    chassis.setPose(30.5, 48, chassis.getPose().theta);
    // resetRobotPos(leftDistance, "positive_y");
    // resetRobotPos(frontDistance, "positive_x");
    Intake.Score();
    Loader.extend();
    pros::delay(2000);
    Intake.In();
    chassis.moveToPoint(54, 48, 2500, {.minSpeed=50, .earlyExitRange=2});
    chassis.waitUntilDone();
    chassis.moveToPoint(60, 48, 2500, {.maxSpeed=40});
    chassis.waitUntilDone();
    // chassis.tank(50, 50);
    // pros::delay(2000);
    // chassis.tank(0, 0);
    wiggle(2250);
    chassis.turnToPoint(30, 48, 1500, {.forwards=false});
    chassis.waitUntilDone();
    chassis.moveToPoint(30, 48, 2500, {.forwards=false, .minSpeed=75});
    chassis.waitUntilDone();
    chassis.tank(-127, -127);
    pros::delay(500);
    chassis.tank(0, 0);
    Intake.Score();
    pros::delay(2500);
    moveRelative(4, 127, 127, 750);
    chassis.waitUntilDone();
    moveRelative(-4, 60, 20, 750);
    chassis.waitUntilDone();
    Intake.Stop();
    chassis.moveToPoint(48, -46, 5000, {.minSpeed=50});
    chassis.waitUntilDone();
    chassis.moveToPoint(48, -52, 7500, {.maxSpeed=80});
    // chassis.moveToPoint(48, -44, 4000, {.maxSpeed=110, .minSpeed=50, .earlyExitRange=1});
    // chassis.moveToPoint(48, -50, 4000, {.maxSpeed=100});
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 1500);
    chassis.waitUntilDone();
    resetRobotPos(frontDistance, "positive_x");
    resetRobotPos(rightDistance, "negative_y");
    Intake.In();
    chassis.moveToPoint(54, -48, 2500, {.minSpeed=50, .earlyExitRange=2});
    chassis.waitUntilDone();
    chassis.moveToPoint(60, -48, 2500, {.maxSpeed=40});
    chassis.waitUntilDone();
    // chassis.tank(50,50);
    // pros::delay(2000);
    // chassis.tank(0, 0);
    wiggle(2250);
    moveRelative(-10, 127, 80, 1250);
    chassis.waitUntilDone();
    Loader.retract();
    Intake.Stop();
    // chassis.moveToPoint(-36, 60, 3000, {.forwards=false, .minSpeed=5, .earlyExitRange=8});
    straightLine(30, -60, 1500, 3000, {.forwards=false}, {.forwards=false, .minSpeed=50, .earlyExitRange=6});
    chassis.waitUntilDone();
    chassis.moveToPoint(-36, -60, 5000, {.forwards=false, .minSpeed=75});
    chassis.waitUntilDone();
    // chassis.moveToPoint(48, 48, 5000, {.forwards=false});
    straightLine(-48, -47, 1500, 3500, {.forwards=false, .minSpeed=20}, {.forwards=false});
    chassis.waitUntilDone();
    chassis.turnToPoint(-30, -48, 1500, {.forwards=false});
    chassis.waitUntilDone();
    chassis.moveToPoint(-31, -48, 2500, {.forwards=false});
    chassis.waitUntilDone();
    chassis.tank(-127, -127);
    pros::delay(750);
    chassis.tank(0, 0);
    chassis.setPose(-30.5, -48, chassis.getPose().theta);
    // resetRobotPos(leftDistance, "negative_y");
    // resetRobotPos(frontDistance, "negative_x");
    Intake.Score();
    Loader.extend();
    pros::delay(2000);
    Intake.In();
    chassis.moveToPoint(-54, -48, 2500, {.minSpeed=50, .earlyExitRange=2});
    chassis.waitUntilDone();
    chassis.moveToPoint(-60, -48, 2500, {.maxSpeed=40});
    chassis.waitUntilDone();
    // chassis.tank(50,50);
    // pros::delay(2000);
    // chassis.tank(0, 0);
    wiggle(2250);
    chassis.moveToPoint(-30, -48, 2500, {.forwards=false});
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(2500);
    moveRelative(4, 127, 127, 750);
    chassis.waitUntilDone();
    moveRelative(-4, 60, 20, 750);
    chassis.waitUntilDone();
    Intake.Stop();
    Loader.retract();
    chassis.moveToPoint(-40, 2, 2500);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1500);
    chassis.waitUntilDone();
    DescoreArm.extend();
    chassis.tank(127, 127);
    pros::delay(1500);
    chassis.tank(0, 0);
    DescoreArm.retract();


}

void driveForward() {
    moveRelative(4, 600, 0, 1000);
    chassis.waitUntilDone();
}

void pidTuning() {
     // set position to x:0, y:0, heading:0
    chassis.setPose(0, 0, 0);
    
    chassis.turnToHeading(90, 10000);
    chassis.waitUntilDone();
    // chassis.moveToPoint(0, 24, 10000);
    // chassis.waitUntilDone();

    // chassis.moveToPoint(0, 0, 10000, {.forwards=false});
    // chassis.waitUntilDone();
    // chassis.turnToHeading(90, 10000);
    // chassis.waitUntilDone();
    // chassis.turnToHeading(180, 10000);
    // chassis.waitUntilDone();
    // chassis.turnToHeading(270, 10000);
    // chassis.waitUntilDone();
    // chassis.turnToHeading(0, 10000);
    // chassis.waitUntilDone();
}