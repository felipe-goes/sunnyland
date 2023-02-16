#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include "types.h"
#include "sprite_eng.h"

// Attributes
extern Sprite *player;
typedef enum {
  PlayerRun,
  PlayerLadder,
  PlayerCrouch,
  PlayerHit,
  PlayerIdle,
  PlayerJump
} SpriteAnimation;

// Functions
extern void loadSprite(const SpriteDefinition *sprite);
extern void animateSprite(SpriteAnimation animation);

// player = SPR_addSprite(&player_sprite, 0, 112,
//                        TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
// SPR_setAnim(player, 4);

#endif // !PLAYER_INCLUDED
