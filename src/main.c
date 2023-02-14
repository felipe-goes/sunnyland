#include <genesis.h>
#include <resources.h>

#define FIX_ZERO FIX16(0)

fix16 xOffset = FIX_ZERO;
fix16 yOffset = FIX_ZERO;
fix16 scrollValues[15] = {FIX_ZERO, FIX_ZERO, FIX_ZERO, FIX_ZERO, FIX_ZERO,
                          FIX_ZERO, FIX_ZERO, FIX_ZERO, FIX_ZERO, FIX_ZERO,
                          FIX_ZERO, FIX_ZERO, FIX_ZERO, FIX_ZERO, FIX_ZERO};
u8 moveSide = 0;

void moveBGBRight() {
  fix16 *scroll;
  scroll = scrollValues;
  for (u8 i = 0; i < 15; i++) {
    *scroll = fix16Add(*scroll, FIX16(-0.03));
    scroll += 1;
  }
}

void moveBGBLeft() {
  fix16 *scroll;
  scroll = scrollValues;
  for (u8 i = 0; i < 15; i++) {
    *scroll = fix16Add(*scroll, FIX16(0.03));
    scroll += 1;
  }
}

void moveForeground() {
  if (moveSide == 1) {
    if (xOffset < 192)
      xOffset = fix16Add(xOffset, FIX16(0.06));
  } else if (moveSide == 2) {
    if (xOffset > 0)
      xOffset = fix16Add(xOffset, FIX16(-0.06));
  } else if (moveSide == 3) {
    if (yOffset > 0)
      yOffset = fix16Add(yOffset, FIX16(-0.06));
  } else if (moveSide == 4) {
    if (yOffset < 24)
      yOffset = fix16Add(yOffset, FIX16(0.06));
  }
}

void myJoyHandler(u16 joy, u16 changed, u16 state) {
  if (joy == JOY_1) {
    if (state & BUTTON_RIGHT) {
      moveSide = 1;
    } else if (state & BUTTON_LEFT) {
      moveSide = 2;
    } else if (state & BUTTON_UP) {
      moveSide = 3;
    } else if (state & BUTTON_DOWN) {
      moveSide = 4;
    } else if ((changed & BUTTON_RIGHT) | (changed & BUTTON_LEFT) |
               (changed & BUTTON_UP) | (changed & BUTTON_DOWN)) {
      moveSide = 0;
    }
  }
}

int main() {
  SYS_disableInts();

  JOY_init();
  JOY_setEventHandler(&myJoyHandler);
  VDP_setPlaneSize(64, 64, TRUE);
  // SPR_init();

  VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_PLANE);

  // Set palettes
  PAL_setPalette(PAL0, bg_b_blue.palette->data, DMA);
  PAL_setPalette(PAL1, stage_palette.data, DMA);

  // Blue background
  u16 ind = TILE_USERINDEX;
  VDP_loadTileSet(bg_b_blue.tileset, ind, DMA);
  VDP_drawImageEx(BG_B, &bg_b_blue, ind, 0, 0, PAL0, DMA);
  ind += bg_b_blue.tileset->numTile;

  Map *stageMap;
  VDP_loadTileSet(&stage_tileset, ind, DMA);
  stageMap = MAP_create(&stage_map, BG_A,
                        TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind));
  ind += stage_tileset.numTile;

  SYS_enableInts();

  while (1) {
    // BG_B
    moveBGBRight();
    VDP_setHorizontalScrollTile(BG_B, 0, scrollValues, 15, DMA);

    // BG_A
    MAP_scrollTo(stageMap, xOffset, yOffset);
    moveForeground();

    // SPR_update();
    SYS_doVBlankProcess();
  }

  return (0);
}
