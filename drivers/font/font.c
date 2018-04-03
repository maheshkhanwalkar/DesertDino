#include "font_raw.h"
#include "../../lib/libg.h"
#include "../video/video.h"
#include "../../myLib.h"

/* Constants */
static const int N_ROWS = 8;
static const int N_COLS = 6;

void draw_char(int row, int col, const char ch, unsigned short color)
{
    for(int r = 0; r < N_ROWS; r++)
    {
        for(int c = 0; c < N_COLS; c++)
        {
            if(fontdata_6x8[idx(r, c, N_COLS) + ch * 48])
                draw_pixel(row + r, col + c, color);
            else
                draw_pixel(row + r, col + c, BLACK);
        }
    }
}

void draw_str(int row, int col, const char* str, unsigned short color)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        draw_char(row, col + i * 6, str[i], color);
    }
}
