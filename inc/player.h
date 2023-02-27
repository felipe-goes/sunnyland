#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include "types.h"
#include "sprite_eng.h"
#include "maths.h"
#include "vdp_bg.h"

#define FIX_ZERO FIX16(0)

// Attributes
typedef struct {
  fix16 positionX;
  fix16 positionY;
  fix16 velocityX;
  fix16 velocityY;
  bool canMove;
  bool flipped;
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
extern void movePlayerUp(void);
extern void movePlayerDown(void);
extern void stopPlayerX(void);
extern void updatePlayerXPosition(void);
extern void updatePlayerYPosition(void);
extern void updateCanMove(bool status);
extern void renderPlayer(void);
extern void setFlipped(bool flip);

#endif // !PLAYER_INCLUDED
