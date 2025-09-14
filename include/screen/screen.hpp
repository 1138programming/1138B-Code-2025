#include "screenClass.hpp"
#include "autos.hpp"
#include "systems/intake.hpp"
#include "systems/drive.hpp"


inline Screen newScreen(
{}, 
{}, 
{{"Left Front", left_motors.get_port(0)}, {"Left Mid", left_motors.get_port(1)}, {"Left Back", left_motors.get_port(2)}, 
{"Right Front", right_motors.get_port(0)}, {"Right Mid", right_motors.get_port(1)},{"Right Back", right_motors.get_port(2)},
{"Intake 1", intakemotors.get_port(0)}, {"Intake 2", intakemotors.get_port(1)}});