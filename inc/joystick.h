#ifndef JOYSTICK_INCLUDED
#define JOYSTICK_INCLUDED

#include "gamestate.h"
#include "player.h"

#include "types.h"
#include "joy.h"
#include "vdp_bg.h"

#include "stage.h"
#include "gamestate.h"


extern void myJoyHandler(u16 joy, u16 changed, u16 state);

#endif // !JOYSTICK_INCLUDED
