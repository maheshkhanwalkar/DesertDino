/* drivers/video/prim.c: drawing primitives */

#include "video.h"
#include "../../myLib.h"

/* Display and control mem-mapped I/O */
static volatile unsigned short* video_buffer = (volatile unsigned short*)0x6000000;
static volatile unsigned short* mode_ctrl = (volatile unsigned short *) 0x4000000;

static volatile unsigned short* scanline_ctr = (volatile unsigned short *)0x4000006;

/* Screen dimensions */
static const int NUM_ROWS = 160;
static const int NUM_COLS = 240;

/* Convert 2D indexing to 1D indexing */
static inline int index(int row, int col)
{
    return row * NUM_COLS + col;
}

void init_mode3(void)
{
    *mode_ctrl = MODE3 | BG2_ENABLE;
}

void draw_pixel(int row, int col, int color)
{
    /* Out of bounds */
    if(row > NUM_ROWS || col > NUM_COLS) {
        return;
    }

    /* Draw pixel */
    video_buffer[index(row, col)] = (unsigned short)color;
}

/* TODO: use DMA to improve performance */
void draw_img(int row, int col, int rdim, int cdim, const unsigned short* img_data)
{
    int spot = 0;

    for(int i = 0; i < rdim; i++)
    {
        for(int j = 0; j < cdim; j++)
        {
            draw_pixel(row + i, col + j, img_data[spot]);
            spot++;
        }
    }
}

void waitForVBlank(void)
{
    while(*scanline_ctr > 160)
        ;

    while(*scanline_ctr < 160)
        ;
}

