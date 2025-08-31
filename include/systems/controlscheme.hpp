#include "api.h"

// controllers

inline pros::Controller master(pros::E_CONTROLLER_MASTER);

void driveControl();
void loaderControl();
void intakeControl(void* param);