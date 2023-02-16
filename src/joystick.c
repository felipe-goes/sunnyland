#include "../inc/joystick.h"
#include "gamestate.h"
#include "vdp_bg.h"

void myJoyHandler(u16 joy, u16 changed, u16 state) {
  if (joy == JOY_1) {
    if (state & BUTTON_A) {
      changeGameState(Debug);
      VDP_clearTextLine(1);
      VDP_drawText("DEBUG MODE", 1, 1);
    } else if (state & BUTTON_B) {
      changeGameState(Production);
      VDP_clearTextLine(1);
      VDP_drawText("PRODUCTION MODE", 1, 1);
    }

    if (getGameState() == Debug) {
      if (state & BUTTON_RIGHT) {
        setHorizontalMove(Right);
      } else if (state & BUTTON_LEFT) {
        setHorizontalMove(Left);
      } else if ((changed & BUTTON_RIGHT) | (changed & BUTTON_LEFT)) {
        setHorizontalMove(NoneH);
      }

      if (state & BUTTON_UP) {
        setVerticalMove(Up);
      } else if (state & BUTTON_DOWN) {
        setVerticalMove(Down);
      } else if ((changed & BUTTON_UP) | (changed & BUTTON_DOWN)) {
        setVerticalMove(NoneV);
      }
    }
  }
}
