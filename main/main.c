/* main.c: entry point of the game */

#include "../drivers/video/video.h"
#include "../drivers/video/image.h"
#include "../assets/img/dinosaur.h"
#include "../assets/img/bg_main.h"
#include "../assets/img/ground.h"
#include "../myLib.h"

void delay(int n)
{
    volatile int x = 0;

    for(int i = 0; i < n * 8000; i++)
        x++;
}

int main(void)
{
    init_mode3();

    /* Create image objects */
    image_t bg = img_Create(0, 0, BG_MAIN_HEIGHT, BG_MAIN_WIDTH, bg_main);
    image_t dino = img_Create(SCREEN_HEIGHT - DINOSAUR_HEIGHT, 0, DINOSAUR_HEIGHT, DINOSAUR_WIDTH, dinosaur);
    image_t grd = img_Create(SCREEN_HEIGHT - GROUND_HEIGHT - 2, 0, GROUND_HEIGHT, GROUND_WIDTH, ground);

    img_Draw(bg);
    img_Draw(dino);
    img_Draw(grd);

    while(1) 
    {
        /* Draw the images */
        waitForVBlank();

        delay(10);
        img_Ticker(grd, -10);
    }
}

