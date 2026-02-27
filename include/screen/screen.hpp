#include "screenClass.hpp"
#include "autos.hpp"
#include "systems/intake.hpp"
#include "systems/drive.hpp"


inline Screen newScreen(
{{&soloPleaseHit, "Solo AWP"}, {&left7splitWing, "Left Side - 4 + 3 (Wing)"}, {&split7DihWing, "Left Side - 4 + 3 (Descore -> Wing)"}, {&right7, "Right Side - 7 (Wing)"}, {&driveForward, "Drive Forward"}, {&skills, "Skills"}}, 
{{&soloPleaseHit, "Solo AWP"}, {&left7splitWing, "Left Side - 4 + 3 (Wing)"}, {&split7DihWing, "Left Side - 4 + 3 (Descore -> Wing)"}, {&right7, "Right Side - 7 (Wing)"}, {&driveForward, "Drive Forward"}, {&skills, "Skills"}}, 
{{"Left Front", left_motors.get_port(0)}, {"Left Mid", left_motors.get_port(1)}, {"Left Back", left_motors.get_port(2)}, 
{"Right Front", right_motors.get_port(0)}, {"Right Mid", right_motors.get_port(1)},{"Right Back", right_motors.get_port(2)},
{"Intake 1", intakemotor.get_port()}, {"Intake 2", hoodmotor.get_port()}});