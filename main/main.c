/* main.c: entry point of the game */

#include "../drivers/video/video.h"
#include "../drivers/video/image.h"
#include "../drivers/font/font.h"

#include "../assets/img/dino/dinosaur.h"
#include "../assets/img/dino/dinosaur_left.h"
#include "../assets/img/dino/dinosaur_right.h"
#include "../assets/img/bg/bg_main.h"
#include "../assets/img/ground/ground.h"

#include "../myLib.h"

/* Game states */
enum State
{
    BEGIN,
    START,
    IN_GAME,
    GAME_OVER
};

/* Function prototypes */
void delay(int n);
void title_screen(image_t* bg, enum State* current);

int main(void)
{
    init_mode3();

    /* Create image objects */
    image_t bg = img_Create(0, 0, BG_MAIN_HEIGHT, BG_MAIN_WIDTH, bg_main);
    /*image_t dino = img_Create(SCREEN_HEIGHT - DINOSAUR_HEIGHT - 1, 10, DINOSAUR_HEIGHT, DINOSAUR_WIDTH, dinosaur);

    image_t dino_left = img_Create(SCREEN_HEIGHT - DINOSAUR_LEFT_HEIGHT - 1, 10, DINOSAUR_LEFT_HEIGHT, DINOSAUR_LEFT_WIDTH, dinosaur_left);
    image_t dino_right = img_Create(SCREEN_HEIGHT - DINOSAUR_RIGHT_HEIGHT - 1, 10, DINOSAUR_RIGHT_HEIGHT, DINOSAUR_RIGHT_WIDTH, dinosaur_right);

    image_t grd = img_Create(SCREEN_HEIGHT - GROUND_HEIGHT, 0, GROUND_HEIGHT, GROUND_WIDTH, ground);

    img_Draw(bg);
    img_Draw(grd);
    img_Draw(dino);*/

    //int which = 0;
    enum State current = BEGIN;

    while(1) 
    {
        /* Draw the images */
        waitForVBlank();

        //draw_char(10, 10, 'A', RED);

        /* Perform action */
        switch(current)
        {
            /* Fallthrough (purposefully) */
            case BEGIN:
            case START:
                title_screen(&bg, &current); 
                break;
            case IN_GAME:
                break;
            case GAME_OVER:
                break;
            default:
                break;
        }

        /*delay(20);

        img_Ticker(grd, -5);

        if(which == -1)
        {
            img_Draw(dino);
            which++;
        }
        else if(which == 0)
        {
            img_Draw(dino_left);
            which++;
        }
        else if(which == 1)
        {
            img_Draw(dino);
            which++;
        }
        else
        {
            img_Draw(dino_right);
            which = -1;
        }*/
    }
}

/* Display title screen */
void title_screen(image_t* bg, enum State* current)
{
    if(*current != START)
    {
        img_Draw(*bg);
        draw_str(5, 80, "Desert Dino", YELLOW);
    }


    /* TODO handle button press */
    *current = START;
}

void delay(int n)
{
    volatile int x = 0;

    for(int i = 0; i < n * 8000; i++)
        x++;
}

