#include "api.h"
#include "classes.hpp"
#include "pros/misc.h"
#include "systems/controlscheme.hpp"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"
#include "systems/drive.hpp"
#include "systems/intake.hpp"

// DT Controls
void driveControl() {
        chassis.arcade(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
}

// Intake Buttons
void intakeControl(void* param) {
    while(true) {
        // Intake.colorSort();
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            Intake.In();
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            Intake.Out();
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            Intake.ScoreUp();
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            Intake.ScoreDown();
        } else {
            Intake.Stop();
        };

        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
            indexer.move_velocity(.25*600);
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) || master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {}
        else {
            indexer.brake();
        }
        // if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        //     Intake.enableSort = !Intake.enableSort;
        // }
        Intake.updateState();
        pros::delay(10);
    }
}