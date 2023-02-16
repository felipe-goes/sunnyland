#include "../inc/stage.h"

#define FIX_ZERO FIX16(0)

Stage stage = {FIX_ZERO, FIX_ZERO, NULL};
MoveHorizontal moveHorizontal = NoneH;
MoveVertical moveVertical = NoneV;

void setHorizontalMove(MoveHorizontal move) { moveHorizontal = move; }
void setVerticalMove(MoveVertical move) { moveVertical = move; }

void loadStage(const TileSet *tileset, const MapDefinition *mapDefinition,
               u16 *vRamIndex) {
  VDP_loadTileSet(tileset, *vRamIndex, DMA);
  stage.map = MAP_create(mapDefinition, BG_A,
                         TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, *vRamIndex));
  *vRamIndex += tileset->numTile;
}

void scrollStage() { MAP_scrollTo(stage.map, stage.xOffset, stage.yOffset); }

void moveStage() {
  switch (moveHorizontal) {
  case Left:
    if (stage.xOffset > 0)
      stage.xOffset = fix16Add(stage.xOffset, FIX16(-0.06));
    break;
  case Right:
    if (stage.xOffset < 192)
      stage.xOffset = fix16Add(stage.xOffset, FIX16(0.06));
    break;
  default:
    moveHorizontal = NoneH;
  }

  switch (moveVertical) {
  case Up:
    if (stage.yOffset > 0)
      stage.yOffset = fix16Add(stage.yOffset, FIX16(-0.06));
    break;
  case Down:
    if (stage.yOffset < 24)
      stage.yOffset = fix16Add(stage.yOffset, FIX16(0.06));
    break;
  default:
    moveVertical = NoneV;
  }
}
