/* main.c: entry point of the game */

#include "../drivers/video/video.h"
#include "../assets/img/dinosaur.h"
#include "../myLib.h"

int main(void)
{
    init_mode3();
    
    int r_pos = SCREEN_HEIGHT - DINOSAUR_HEIGHT;
    int c_pos = 0;

    draw_img(r_pos, c_pos, DINOSAUR_HEIGHT, DINOSAUR_WIDTH, dinosaur);
    while(1);
}


