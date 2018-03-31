#pragma once

/**
 * Switches the graphics mode to Mode 3
 */
void init_mode3(void);

/* Color macro */

/* Ideally, this should be replaced with a inlined function;
 * however, since constexpr isn't available in C, the enum
 * definition would become unnecessary messy */
#define COLOR(r,g,b) ((r) + ((g) << 5) + ((b) << 10))

/* Screen dimension macros */
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

/* Basic colors */
enum Colors {
    RED = COLOR(0x1F, 0, 0),
    GREEN = COLOR(0, 0x1F, 0),
    BLUE = COLOR(0, 0, 0x1F),
    WHITE = COLOR(0x1F, 0x1F, 0x1F)
};


/**
 * Draws a pixel with color 'color' at (row, col).
 * If (row, col) is out of bounds, nothing is drawn
 */
void draw_pixel(int row, int col, int color);

/**
 * Wait for the starting of the vblank phase of the GBA
 *
 * If the vblank phase hasn't started yet, the function will
 * wait until the phase starts
 *
 * If the vblank phase has already started, but is not at the
 * beginning, then wait until the next vblank phase
 */
void waitForVBlank(void);

/**
 * Draw an image at (row, col) with dimensions (rdim, cdim) 
 * located in the buffer img_data. Currently does not support DMA.
 */
void draw_img(int row, int col, int rdim, int cdim, 
        const unsigned short* img_data);

