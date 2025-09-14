#include "autos.hpp"
#include "pros/rtos.hpp"
#include "systems/classes.hpp"
#include "systems/drive.hpp"
#include "systems/intake.hpp"
#include "systems/loader.hpp"

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

void leftAuto() {
    chassis.setPose(-48,12,0);
    chassis.moveToPoint(-48, 48, 750, {.maxSpeed=(127*0.5)});
    chassis.waitUntilDone();
    chassis.turnToHeading(135, 750);
    chassis.waitUntilDone();
    Intake.In();
    chassis.moveToPoint(-20, 20, 2500, {.maxSpeed=(127*0.33)});
    chassis.waitUntilDone();
    chassis.moveToPoint(-48, 46, 2500, {.forwards=false, .maxSpeed=(127*0.5)});
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 1200);
    chassis.waitUntilDone();
    chassis.moveToPoint(-28, 46, 2500, {.maxSpeed=(127*0.5)});
    chassis.waitUntilDone();
    moveRelative(-1, 127*0.33, 750);
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(2000);
    Intake.Stop();
    moveRelative(-12, 127*0.5, 1500);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1000);
    chassis.waitUntilDone();
}

void rightAuto() {
    chassis.setPose(-48,-18,180);
    chassis.moveToPoint(-48, -48, 750, {.maxSpeed=(127*0.5)});
    chassis.waitUntilDone();
    chassis.turnToHeading(45, 1250);
    chassis.waitUntilDone();
    Intake.In();
    chassis.moveToPoint(-20, -20, 2500, {.maxSpeed=(127*0.33)});
    chassis.waitUntilDone();
    chassis.moveToPoint(-48, -46, 2500, {.forwards=false, .maxSpeed=(127*0.5)});
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 1200);
    chassis.waitUntilDone();
    chassis.moveToPoint(-28, -46, 2500, {.maxSpeed=(127*0.5)});
    chassis.waitUntilDone();
    moveRelative(-1, 127*0.33, 750);
    chassis.waitUntilDone();
    Intake.Score();
    pros::delay(2000);
    Intake.Stop();
    moveRelative(-12, 127*0.5, 1500);
    chassis.waitUntilDone();
    chassis.turnToHeading(270, 1000);
    chassis.waitUntilDone();
}