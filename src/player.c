#include "../inc/player.h"

#include "stage.h"

Player player = {FIX16(0), FIX16(112), FIX_ZERO, FIX16(1.0), TRUE, NULL};

void loadSprite(const SpriteDefinition *sprite) {
  player.sprite = SPR_addSprite(sprite, fix16ToInt(player.positionX),
                                fix16ToInt(player.positionY),
                                TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
}

void animateSprite(SpriteAnimation animation) {
  SPR_setAnim(player.sprite, animation);
}

void movePlayerRight() {
  animateSprite(PlayerRun);
  SPR_setHFlip(player.sprite, FALSE);
  player.velocityX = FIX16(1.5);
}
void movePlayerLeft() {
  animateSprite(PlayerRun);
  SPR_setHFlip(player.sprite, TRUE);
  player.velocityX = FIX16(-1.5);
}
void stopPlayerX() {
  animateSprite(PlayerIdle);
  player.velocityX = FIX16(0);
}

void updateCanMove(bool status) { player.canMove = status; }

void updatePlayerPosition() {
  // Update X and Y axis
  if (player.canMove) {
    fix16 xPosTemp = fix16Add(player.positionX, player.velocityX);
    fix16 yPosTemp = fix16Add(player.positionY, player.velocityY);

    // Vallidate position
    if (fix16ToInt(xPosTemp) < 0) {
      xPosTemp = FIX_ZERO;
    } else if ((fix16ToInt(xPosTemp) + 32) > 320) {
      xPosTemp = FIX16(288);
    }

    u16 xIntTemp = fix16ToInt(xPosTemp);
    u16 yIntTemp = fix16ToInt(yPosTemp);

    u8 xIndex = xIntTemp / 8;
    u8 yIndex = yIntTemp / 8;
    if (!getCollisionMap(xIndex, yIndex) &&
        !getCollisionMap(xIndex, yIndex + 4) &&
        !getCollisionMap(xIndex + 4, yIndex) &&
        !getCollisionMap(xIndex + 4, yIndex + 4)) {
      player.positionY = yPosTemp;
    }
    player.positionX = xPosTemp;
  }

  // Render
  SPR_setPosition(player.sprite, fix16ToInt(player.positionX),
                  fix16ToInt(player.positionY));
}
