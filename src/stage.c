#include "../inc/stage.h"

#include "player.h"

#define FIX_ZERO FIX16(0)

Stage stage = {FIX_ZERO, FIX_ZERO, NULL};
MoveHorizontal moveHorizontal = NoneH;
MoveVertical moveVertical = NoneV;

void setHorizontalMove(MoveHorizontal move) { moveHorizontal = move; }
void setVerticalMove(MoveVertical move) { moveVertical = move; }

void loadStage(const TileSet *stageTileset, const MapDefinition *stageMap,
               const TileSet *collisionTileset,
               const MapDefinition *collisionMap, u16 *vRamIndex) {
  // Load stage
  VDP_loadTileSet(stageTileset, *vRamIndex, DMA);
  stage.map = MAP_create(stageMap, BG_A,
                         TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, *vRamIndex));
  *vRamIndex += stageTileset->numTile;

  // Load map
  stage.collision =
      MAP_create(collisionMap, NULL, TILE_ATTR(PAL0, FALSE, FALSE, FALSE));

  u8 x = 0, y = 0;
  for (u16 i = 0; i < 2048; i++) {
    x = i % 64;
    y = i / 64;

    stage.collisionTiles[x][y] = MAP_getTile(stage.collision, x, y);
  }
}

void scrollStage() {
  MAP_scrollTo(stage.map, fix16ToInt(stage.xOffset), fix16ToInt(stage.yOffset));
}

void moveStage() {
  switch (moveHorizontal) {
  case Left:
    updateCanMove(TRUE);
    if (fix16ToInt(stage.xOffset) > 0) {
      if ((fix16ToInt(player.positionX) + 16) < 160) {
        stage.xOffset = fix16Add(stage.xOffset, FIX16(-1.5));
        updateCanMove(FALSE);
      }
    } else {
      stage.xOffset = FIX_ZERO;
    }
    break;
  case Right:
    updateCanMove(TRUE);
    if (fix16ToInt(stage.xOffset) < 192) {
      if ((fix16ToInt(player.positionX) + 16) > 160) {
        stage.xOffset = fix16Add(stage.xOffset, FIX16(1.5));
        updateCanMove(FALSE);
      }
    } else {
      stage.xOffset = FIX16(192);
    }
    break;
  default:
    updateCanMove(TRUE);
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

u16 getCollisionMap(u8 x, u8 y) { return stage.collisionTiles[x][y]; }
