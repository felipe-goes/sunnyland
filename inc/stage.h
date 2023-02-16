#ifndef STAGE_INCLUDED
#define STAGE_INCLUDED

#include "types.h"
#include "maths.h"
#include "map.h"

// Attributes
typedef enum { Left, Right, NoneH } MoveHorizontal;
typedef enum { Up, Down, NoneV } MoveVertical;

typedef struct {
  fix16 xOffset;
  fix16 yOffset;
  Map *map;
} Stage;

extern Stage stage;
extern MoveHorizontal moveHorizontal;
extern MoveVertical moveVertical;

// Functions
extern void loadStage(const TileSet *tileset,
                      const MapDefinition *mapDefinition, u16 *vRamIndex);
extern void scrollStage(void);
extern void moveStage(void);
extern void setHorizontalMove(MoveHorizontal move);
extern void setVerticalMove(MoveVertical move);

#endif // !STAGE_INCLUDED
