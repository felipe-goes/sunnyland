#include "../inc/joystick.h"

#include "player.h"
#include "stage.h"

void myJoyHandler(u16 joy, u16 changed, u16 state) {
  if (joy == JOY_1) {
    if (state & BUTTON_RIGHT) {
      movePlayerRight();
      setHorizontalMove(Right);
    } else if (state & BUTTON_LEFT) {
      movePlayerLeft();
      setHorizontalMove(Left);
    } else if ((changed & BUTTON_RIGHT) | (changed & BUTTON_LEFT)) {
      stopPlayerX();
      setHorizontalMove(NoneH);
    }
  }
}
