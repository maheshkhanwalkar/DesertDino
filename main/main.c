/* main.c: entry point of the game */

#include "../drivers/video/prim.h"

#define REG_DISPCTL *(unsigned short *)0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)

unsigned short *videoBuffer = (unsigned short *)0x6000000;

int main() {
    int row = 10;
    int col = 10;
    
    init_mode3();
    draw_pixel(row, col, BLUE /*0x7fff*/);
    
    while(1);
}


