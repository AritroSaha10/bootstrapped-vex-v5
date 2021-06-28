#include "main.h"
#include "chassis.h"
#include "globals.h"

pros::ADIEncoder bEnc(BENC_PORT_TOP, BENC_PORT_BOT, true);
pros::ADIEncoder lEnc(LENC_PORT_TOP, LENC_PORT_BOT, false);
pros::ADIEncoder rEnc(RENC_PORT_TOP, RENC_PORT_BOT, true);