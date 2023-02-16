#ifndef BACKGROUND_INCLUDED
#define BACKGROUND_INCLUDED

#include "types.h"
#include "maths.h"
#include "vdp_bg.h"
#include "vdp_pal.h"

// Attributes
typedef struct {
  u16 oceanColor;
  u16 swapColor;
  fix16 scrollValues[15];
} Background;

extern Background cloud_ocean;

// Functions
extern void moveBGBRight(void);
extern void scrollBrackground(void);
extern bool swapColors(u32 countFrame);
extern void loadBackground(const Image background, u16 *vRamIndex);

// Constructor
extern void backgroundInit(void);

#endif // !BACKGROUND_INCLUDED
