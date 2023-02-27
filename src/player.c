#include "../inc/player.h"

#include "stage.h"

Player player = {FIX16(0), FIX16(120), FIX_ZERO, FIX16(1.0), TRUE, FALSE, NULL};

void setFlipped(bool flip) { player.flipped = flip; }

void loadSprite(const SpriteDefinition *sprite) {
  player.sprite = SPR_addSprite(sprite, fix16ToInt(player.positionX),
                                fix16ToInt(player.positionY),
                                TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
}

void animateSprite(SpriteAnimation animation) {
  SPR_setAnim(player.sprite, animation);
}

void movePlayerRight() {
  player.flipped = FALSE;
  if (getVerticalMove() == Down) {
    animateSprite(PlayerRun);
    SPR_setHFlip(player.sprite, player.flipped);
  }
  player.velocityX = FIX16(1.5);
}
void movePlayerLeft() {
  player.flipped = TRUE;
  if (getVerticalMove() == Down) {
    animateSprite(PlayerRun);
    SPR_setHFlip(player.sprite, player.flipped);
  }
  player.velocityX = FIX16(-1.5);
}
void movePlayerUp() {
  animateSprite(PlayerJump);
  player.velocityY = FIX16(-1.0);
}
void movePlayerDown() {
  animateSprite(PlayerJump);
  player.velocityY = FIX16(1.0);
}

void stopPlayerX() {
  animateSprite(PlayerIdle);
  player.velocityX = FIX16(0);
}

void updateCanMove(bool status) { player.canMove = status; }

void updatePlayerXPosition() {
  if (player.canMove) {
    fix16 xPosTemp = fix16Add(player.positionX, player.velocityX);
    u8 xIndex;
    u8 yIndex = fix16ToInt(player.positionY) / 8;
    bool collisionArray[3];

    switch (getHorizontalMove()) {
    case Right:
      // Vallidate position
      xIndex = fix16ToInt(xPosTemp) / 8;

      if (fix16ToInt(xPosTemp) + 32 > 320) {
        xPosTemp = FIX16(296);
      } else {
        collisionArray[0] = getCollisionMap(xIndex + 2, yIndex);
        collisionArray[1] = getCollisionMap(xIndex + 2, yIndex + 1);
        collisionArray[1] = getCollisionMap(xIndex + 2, yIndex + 2);

        if (!collisionArray[0] && !collisionArray[1] && !collisionArray[2]) {
          player.positionX = xPosTemp;
        }
      }
      break;

    case Left:
      // Vallidate position
      xIndex = fix16ToInt(xPosTemp) / 8;

      if (fix16ToInt(xPosTemp) < 0) {
        player.positionX = FIX_ZERO;
      } else {
        collisionArray[0] = getCollisionMap(xIndex + 1, yIndex);
        collisionArray[1] = getCollisionMap(xIndex + 1, yIndex + 1);
        collisionArray[2] = getCollisionMap(xIndex + 1, yIndex + 2);

        if (!collisionArray[0] && !collisionArray[1] && !collisionArray[2]) {
          player.positionX = xPosTemp;
        }
      }
      break;

    default:
      // do nothing
      break;
    }
  }
}

void updatePlayerYPosition() {
  fix16 yPosTemp = fix16Add(player.positionY, player.velocityY);
  u8 xIndex = fix16ToInt(player.positionX) / 8;
  u8 yIndex = (fix16ToInt(yPosTemp) - 2) / 8;
  bool collisionArray[2];

  switch (getVerticalMove()) {
  case Up:
    // Vallidate position
    if (fix16ToInt(yPosTemp) < 0) {
      yPosTemp = FIX_ZERO;
    } else {

      collisionArray[0] = getCollisionMap(xIndex, yIndex);
      collisionArray[1] = getCollisionMap(xIndex + 2, yIndex);

      if (!collisionArray[0] && !collisionArray[1]) {
        player.positionY = yPosTemp;
      }
    }
    break;

  case Down:
    // Vallidate position
    if (fix16ToInt(yPosTemp) + 24 > 224) {
      yPosTemp = FIX16(200);
    } else {
      collisionArray[0] = getCollisionMap(xIndex + 1, yIndex + 3);
      collisionArray[1] = getCollisionMap(xIndex + 2, yIndex + 3);

      if (!collisionArray[0] && !collisionArray[1]) {
        player.positionY = yPosTemp;
      }
    }
    break;

  default:
    // do nothing
    break;
  }
}

void renderPlayer() {
  // Render
  SPR_setPosition(player.sprite, fix16ToInt(player.positionX),
                  fix16ToInt(player.positionY));
}
