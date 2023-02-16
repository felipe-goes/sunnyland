#include <genesis.h>
#include <resources.h>

#include "../inc/background.h"
#include "../inc/stage.h"
#include "../inc/joystick.h"
#include "../inc/gamestate.h"

#define FIX_ZERO FIX16(0)

Sprite *player;

int main() {
  // SGDK initialization
  SYS_disableInts();

  JOY_init();
  JOY_setEventHandler(&myJoyHandler);
  SPR_initEx(336);

  VDP_setPlaneSize(64, 32, TRUE);
  VDP_setScrollingMode(HSCROLL_TILE, VSCROLL_PLANE);

  // Set palettes
  PAL_setPalette(PAL0, bg_b_blue.palette->data, DMA);
  PAL_setPalette(PAL1, stage_palette.data, DMA);
  PAL_setPalette(PAL2, player_sprite.palette->data, DMA);

  // Blue background
  u16 vRamIndex = TILE_USERINDEX;
  backgroundInit();
  loadBackground(bg_b_blue, &vRamIndex);

  // Stage foreground
  loadStage(&stage_tileset, &stage_map, &vRamIndex);

  // Sprites
  player = SPR_addSprite(&player_sprite, 0, 112,
                         TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
  SPR_setAnim(player, 4);

  SYS_enableInts();

  u32 countFrame = 0;
  while (1) {
    countFrame++;
    if (swapColors(countFrame))
      countFrame = 0;

    // Background
    moveBGBRight();
    scrollBrackground();

    // Foreground
    scrollStage();
    moveStage();
    // MAP_scrollTo(stageMap, xOffset, yOffset);
    // moveForeground();

    SPR_update();
    SYS_doVBlankProcess();
  }

  return (0);
}
