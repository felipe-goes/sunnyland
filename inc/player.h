#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include "types.h"
#include "sprite_eng.h"
#include "maths.h"

#define FIX_ZERO FIX16(0)

// Attributes
typedef struct {
  fix16 positionX;
  fix16 positionY;
  fix16 velocityX;
  fix16 velocityY;
  bool canMove;
  Sprite *sprite;
} Player;
extern Player player;

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
extern void movePlayerRight(void);
extern void movePlayerLeft(void);
extern void stopPlayerX(void);
extern void updatePlayerPosition(void);
extern void updateCanMove(bool status);

#endif // !PLAYER_INCLUDED
