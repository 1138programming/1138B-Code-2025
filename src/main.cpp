#include "main.h"
#include "systems/classes.hpp"
#include "systems/drive.hpp"
#include "systems/intake.hpp"
#include "systems/controlscheme.hpp"
#include "autos.hpp"
#include "screen/screen.hpp"
#include "taskmanager/taskmanager.hpp"


TaskWrapper intakeControlThread(intakeControl, nullptr, "Intake Control");

TaskManager controlsManager;



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initilizeControls() {
	controlsManager.addTask(&intakeControlThread);
	controlsManager.startAllTasks();
}

void initialize() {

	pros::delay(500);

	chassis.calibrate();

	newScreen.init(10);

	Intake.setSpeed(127);
	Intake.setSortColor(pros::Color::blue);

	initilizeControls();

	
	pros::Task([&] {
        while (true) {
            auto p = chassis.getPose();
            newScreen.print(0, "X: %f", (p.x));
            newScreen.print(1, "Y: %f", (p.y));
            newScreen.print(2, "Theta: %f", (p.theta));
			newScreen.updateMotorData();
			// if (Intake.enableSort) {
			// 	master.print(0, 0, "Keeping %s     ", Intake.getSortColor());
			// }
			// else {
			// 	master.print(0, 0, "Sorting Off    ");
			// };
            pros::delay(10);
        }
    });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	newScreen.setPage(Screen::HOME);
}
/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous() {
	float startTime = pros::millis();
	newScreen.setPage(Screen::LOGO);
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
	// skills();
	left7splitWing();
	// right7();
	// pidTuning();
	// newScreen.runSelected();
	float endTime = pros::millis();
    float totalTime = (endTime - startTime)/1000;
    std::cout << totalTime << std::endl;
    master.print(0,0,"%f", totalTime);
}

void opcontrol() {
	if (pros::competition::is_field_control()) {newScreen.setPage(Screen::LOGO);};
	while (true) {
		driveControl();
		loaderControl();
		controlsManager.checkAndRestartTasks();				 
		pros::delay(20);
	}
}