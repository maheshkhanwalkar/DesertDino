#pragma once

/**
 * Switches the graphics mode to Mode 3
 */
void init_mode3(void);

/* Default colors */
#define COLOR(r,g,b) ((r) + ((g) << 5) + ((b) << 10))

enum Colors {
    RED = COLOR(0xFF, 0, 0),
    GREEN = COLOR(0, 0xFF, 0),
    BLUE = COLOR(0, 0, 0xFF)
};


/**
 * Draws a pixel with color 'color' at (row, col).
 * If (row, col) is out of bounds, nothing is drawn
 */
void draw_pixel(int row, int col, int color);

