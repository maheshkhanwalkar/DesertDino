/* drivers/video/prim.c: drawing primitives */

#include "video.h"
#include "../../myLib.h"
#include "../../lib/libg.h"

/* Display and control mem-mapped I/O */
static volatile unsigned short* video_buffer = (volatile unsigned short*)0x6000000;
static volatile unsigned short* mode_ctrl = (volatile unsigned short *) 0x4000000;

static volatile unsigned short* scanline_ctr = (volatile unsigned short *)0x4000006;

/* Screen dimensions */
static const int NUM_ROWS = 160;
static const int NUM_COLS = 240;

/* Convert 2D indexing to 1D indexing */
/*static inline int index(int row, int col, int c_count)
{
    return row * c_count + col;
}*/

/*static inline int index(int row, int col)
{
    return row * NUM_COLS + col;
}*/

void init_mode3(void)
{
    *mode_ctrl = MODE3 | BG2_ENABLE;
}

void draw_pixel(int row, int col, int color)
{
    /* Out of bounds */
    if(row > NUM_ROWS || col > NUM_COLS) 
    {
        return;
    }

    /* Draw pixel */
    video_buffer[idx(row, col, NUM_COLS)] = (unsigned short)color;
}

void draw_img(int row, int col, int rdim, int cdim, const unsigned short* img_data)
{
    int spot = 0;

    for(int r = 0; r < rdim; r++)
    {
        DMA[3].src = &img_data[spot];
        DMA[3].dst = &video_buffer[idx(row + r, col, NUM_COLS)];
        DMA[3].cnt = cdim | DMA_ON | DMA_NOW;

        spot += cdim;
    }
}

void waitForVBlank(void)
{
    while(*scanline_ctr > 160)
        ;

    while(*scanline_ctr < 160)
        ;
}

