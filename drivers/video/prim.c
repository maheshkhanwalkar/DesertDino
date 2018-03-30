/* drivers/video/prim.c: drawing primitives */

#define MODE3 3
#define BG2_ENABLE  (1<<10)

/* Display and control mem-mapped I/O */
static volatile unsigned short* video_buffer = (volatile unsigned short*)0x6000000;
static volatile unsigned short* mode_ctrl = (volatile unsigned short *) 0x4000000;

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

