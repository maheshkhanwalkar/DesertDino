/* main.c: entry point of the game */

#include "../drivers/video/video.h"
#include "../assets/img/dinosaur.h"
#include "../assets/img/bg_title.h"
#include "../myLib.h"

int main(void)
{
    init_mode3();
    
    int r_pos = SCREEN_HEIGHT - DINOSAUR_HEIGHT;
    int c_pos = 0;

    /*for(int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for(int j = 0; j < SCREEN_WIDTH; j++)
        {
            draw_pixel(i, j, RED);
        }
    }*/

    draw_img(0, 0, BG_TITLE_HEIGHT, BG_TITLE_WIDTH, bg_title); 
    draw_img(r_pos, c_pos, DINOSAUR_HEIGHT, DINOSAUR_WIDTH, dinosaur);
    while(1);
}


