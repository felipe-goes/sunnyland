#include "../inc/player.h"

Player player = {intToFix16(0), intToFix16(112), FIX_ZERO, FIX_ZERO, NULL};

void loadSprite(const SpriteDefinition *sprite) {
  player.sprite = SPR_addSprite(sprite, fix16ToInt(player.positionX),
                                fix16ToInt(player.positionY),
                                TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
}

void animateSprite(SpriteAnimation animation) {
  SPR_setAnim(player.sprite, animation);
}

void movePlayerRight() {
  // player.velocityX = fix16Add(player.velocityX, FIX16(0.05));
  animateSprite(PlayerRun);
  SPR_setHFlip(player.sprite, FALSE);
  player.velocityX = FIX16(1.5);
}
void movePlayerLeft() {
  // player.velocityX = fix16Add(player.velocityX, FIX16(-0.05));
  animateSprite(PlayerRun);
  SPR_setHFlip(player.sprite, TRUE);
  player.velocityX = FIX16(-1.5);
}
void stopPlayerX() {
  animateSprite(PlayerIdle);
  player.velocityX = FIX16(0);
}

void updatePlayerPosition() {
  // if (player.positionX > 0 && player.positionX < 640)
  player.positionX += player.velocityX;
  SPR_setPosition(player.sprite, fix16ToInt(player.positionX),
                  fix16ToInt(player.positionY));
}
