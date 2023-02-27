#include <genesis.h>
#include <resources.h>

#include "../inc/background.h"
#include "../inc/stage.h"
#include "../inc/joystick.h"
#include "../inc/player.h"

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
  loadStage(&stage_tileset, &stage_map, &collision_tileset, &collision_map,
            &vRamIndex);

  // Player
  loadSprite(&player_sprite);
  animateSprite(PlayerIdle);
  updatePlayerXPosition();
  updatePlayerYPosition();

  SYS_enableInts();

  u32 countFrame = 0;
  u16 tileInfo = 0;
  u8 x = 0, y = 0;
  char text[6];
  while (TRUE) {
    countFrame++;
    // Animate ocean
    if (swapColors(countFrame))
      countFrame = 0;

    // DEBUG
    // Show tile map metadata
    // if (y < 32) {
    //   if (x > 63) {
    //     x = 0;
    //     y++;
    //   }
    //   tileInfo = getCollisionMap(x, y);
    //   sprintf(text, "%d", tileInfo);
    //   VDP_drawText(text, x, y);
    //   x++;
    // } else {
    //   x = 0;
    //   y = 0;
    // }

    // Background
    moveBGBRight();
    scrollBrackground();

    // Foreground
    scrollStage();
    moveStage();

    // Player
    updatePlayerXPosition();
    updatePlayerYPosition();
    renderPlayer();

    SPR_update();
    SYS_doVBlankProcess();
  }

  return (0);
}
