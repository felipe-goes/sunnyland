#include "../inc/background.h"

#define FIX_ZERO FIX16(0)
#define OCEAN 5
#define SWAP 7

Background cloud_ocean = {-1,
                          -1,
                          {FIX_ZERO, FIX_ZERO, FIX_ZERO, FIX_ZERO, FIX_ZERO,
                           FIX_ZERO, FIX_ZERO, FIX_ZERO, FIX_ZERO, FIX_ZERO,
                           FIX_ZERO, FIX_ZERO, FIX_ZERO, FIX_ZERO, FIX_ZERO}};

void backgroundInit() {
  cloud_ocean.oceanColor = VDP_getPaletteColor(OCEAN);
  cloud_ocean.swapColor = VDP_getPaletteColor(SWAP);
}

void loadBackground(const Image background, u16 *vRamIndex) {
  VDP_loadTileSet(background.tileset, *vRamIndex, DMA);
  VDP_drawImageEx(BG_B, &background, *vRamIndex, 0, 0, PAL0, DMA);
  *vRamIndex = *vRamIndex + background.tileset->numTile;
}

void moveBGBRight() {
  fix16 *scroll;
  scroll = cloud_ocean.scrollValues;
  for (u8 i = 0; i < 15; i++) {
    *scroll = fix16Add(*scroll, FIX16(-0.03));
    scroll += 1;
  }
}

void scrollBrackground() {
  VDP_setHorizontalScrollTile(BG_B, 0, cloud_ocean.scrollValues, 15, DMA);
}

bool swapColors(u32 countFrame) {
  bool overflowed = FALSE;

  // if (countFrame > 4294967280) {
  if (countFrame > 240) {
    countFrame = 0;
    overflowed = TRUE;
  }

  if ((countFrame % 120) == 0) {
    VDP_setPaletteColor(OCEAN, cloud_ocean.oceanColor);
  } else if ((countFrame % 60) == 0) {
    VDP_setPaletteColor(OCEAN, cloud_ocean.swapColor);
  }

  return overflowed;
}
