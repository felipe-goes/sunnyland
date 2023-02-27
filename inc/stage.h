#ifndef STAGE_INCLUDED
#define STAGE_INCLUDED

#include "types.h"
#include "maths.h"
#include "map.h"

// Attributes
typedef enum { Left, Right, NoneH } MoveHorizontal;
typedef enum { Up, Down } MoveVertical;

typedef struct {
  fix16 xOffset;
  fix16 yOffset;
  Map *map;
  Map *collision;
  u16 collisionTiles[64][32];
} Stage;

extern Stage stage;
extern MoveHorizontal moveHorizontal;
extern MoveVertical moveVertical;

// Functions
extern void loadStage(const TileSet *stageTileset,
                      const MapDefinition *stageMap,
                      const TileSet *collisionTileset,
                      const MapDefinition *collisionMap, u16 *vRamIndex);
extern void scrollStage(void);
extern void moveStage(void);
extern void setHorizontalMove(MoveHorizontal move);
extern MoveHorizontal getHorizontalMove(void);
extern void setVerticalMove(MoveVertical move);
extern MoveVertical getVerticalMove(void);
extern u16 getCollisionMap(u8 x, u8 y);

#endif // !STAGE_INCLUDED
