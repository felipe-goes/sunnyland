#include "../inc/player.h"

Sprite *player = NULL;

void loadSprite(const SpriteDefinition *sprite) {
  player = SPR_addSprite(sprite, 0, 112, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
}

void animateSprite(SpriteAnimation animation){
  SPR_setAnim(player, animation);
}
