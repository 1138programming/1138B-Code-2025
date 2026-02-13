#include "api.h"
#include "classes.hpp"
#include "pros/misc.h"
#include "systems/controlscheme.hpp"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"
#include "systems/drive.hpp"
#include "systems/intake.hpp"
#include "systems/loader.hpp"

// DT Controls
void driveControl() {
        chassis.arcade(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
}

// Intake Buttons
void intakeControl(void* param) {
    bool skillsMode = false;
    master.print(0, 0, "%s", skillsMode ? "Skills" : "Match ");
    while(true) {
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
            skillsMode = !skillsMode;
        }
        // Intake.colorSort();
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
            Intake.Score();
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) && !skillsMode) {
            Intake.ScoreMid();
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) && skillsMode) {
            Intake.ScoreMidSlow();
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            Intake.In();
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            Intake.Out();
        } else if (!pros::competition::is_autonomous()) {
            Intake.Stop();
        };
        // if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        //     Intake.enableSort = !Intake.enableSort;
        // }
        Intake.Updater();
        pros::delay(10);
    }
}

// Loader Control
void loaderControl() {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        Loader.toggle();
    }
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
        DescoreArm.toggle();
    }
    MidDescoreArm.set_value(master.get_digital(pros::E_CONTROLLER_DIGITAL_X));
}