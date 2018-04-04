/* main.c: entry point of the game */

#include "../drivers/video/video.h"
#include "../drivers/video/image.h"
#include "../drivers/font/font.h"

#include "../assets/img/dino/dinosaur.h"
#include "../assets/img/dino/dinosaur_left.h"
#include "../assets/img/dino/dinosaur_right.h"
#include "../assets/img/dino/dinosaur_none.h"

#include "../assets/img/bg/bg_main.h"
#include "../assets/img/bg/bg_dark.h"

#include "../assets/img/ground/ground.h"

#include "../myLib.h"

#include <stdbool.h>

/* Game states */
enum State
{
    START,
    IN_GAME,
    GAME_OVER,
};

/* Function prototypes */
void delay(int n);

void title_screen(enum State* current);
void in_game(image_t bg[4], enum State* current, bool* rs);

int main(void)
{
    init_mode3();

    /* Create image objects */
    image_t bg_title = img_Create(0, 0, BG_DARK_HEIGHT, BG_DARK_WIDTH, bg_dark);
    image_t bg_ms = img_Create(0, 0, BG_MAIN_HEIGHT, BG_MAIN_WIDTH, bg_main);

    image_t dino = img_Create(SCREEN_HEIGHT - DINOSAUR_HEIGHT - 1, 10, DINOSAUR_HEIGHT, DINOSAUR_WIDTH, dinosaur);
    image_t dino_left = img_Create(SCREEN_HEIGHT - DINOSAUR_LEFT_HEIGHT - 1, 10, DINOSAUR_LEFT_HEIGHT, DINOSAUR_LEFT_WIDTH, dinosaur_left);
    image_t dino_right = img_Create(SCREEN_HEIGHT - DINOSAUR_RIGHT_HEIGHT - 1, 10, DINOSAUR_RIGHT_HEIGHT, DINOSAUR_RIGHT_WIDTH, dinosaur_right);
    image_t dino_none = img_Create(SCREEN_HEIGHT - DINOSAUR_NONE_HEIGHT - 1, 10, DINOSAUR_NONE_HEIGHT, DINOSAUR_NONE_WIDTH, dinosaur_none);
    

    image_t grd = img_Create(SCREEN_HEIGHT - GROUND_HEIGHT, 0, GROUND_HEIGHT, GROUND_WIDTH, ground);
    image_t imgs[4] = { dino, dino_none, grd, bg_ms };

    int which = 0;
    enum State current = START;

    bool s_once = false;
    bool g_once = false;
    bool restart = false;

    while(1) 
    {
        /* Draw the images */
        waitForVBlank();

        /* Perform action */
        switch(current)
        {
            case START:
                if(!s_once) {
                    img_Draw(bg_title);

                    draw_str(5, 80, "Desert Dino", YELLOW);
                    draw_str(25, 50, "Press 'Start' to Begin", YELLOW);
 
                    s_once = true;
                }

                title_screen(&current);
                break;
            case IN_GAME:
                if(!g_once) {
                    img_Draw(bg_ms);
                    g_once = true;
                }

                if(which == -1) {
                    imgs[0] = dino;
                    which++;
                } else if(which == 0) {
                    imgs[0] = dino_left;
                    which++;
                } else if(which == 1) {
                    imgs[0] = dino;
                    which++;
                } else {
                    imgs[0] = dino_right;
                    which = -1;
                }
  
                in_game(imgs, &current, &restart);

                if(restart){
                    current = false;
                    s_once = false;
                    g_once = false;
                    restart = false;
                }

                break;
            case GAME_OVER:
                break;
            default:
                break;
        }
    }
}

/* Display title screen */
void title_screen(enum State* current)
{
    /* Start pressed */
    if(KEY_DOWN_NOW(BUTTON_START))
    {
        *current = IN_GAME;
        return;
    }

    *current = START;
}

/* Render in-game content */
void in_game(image_t imgs[4], enum State* current, bool* restart)
{
    /* Air time */
    static bool in_air = false;
    static int ticks = 0;

    /* Get images */
    image_t dino = imgs[0];
    image_t dino_none = imgs[1];
    image_t grd = imgs[2];
    image_t bg = imgs[3];


    if(KEY_DOWN_NOW(BUTTON_SELECT))
    {
        *restart = true;
        *current = START;

        return;
    }

    if(KEY_DOWN_NOW(BUTTON_UP))
    {
        if(!in_air)
            in_air = true;
    }

    img_Ticker(grd, -5);

    if(in_air)
    {
        if(ticks < 5) 
        {
            img_RelMove(dino_none, bg, -10, 0);
            ticks++;
        }
        else if(ticks < 10)
        {
            img_RelMove(dino_none, bg, 10, 0);
            ticks++;
        }
        else
        {
            ticks = 0;
            in_air = false;
        }
    }
    else
    {
        img_Draw(dino);
    }

    delay(20);

    *current = IN_GAME;
}

void delay(int n)
{
    volatile int x = 0;

    for(int i = 0; i < n * 8000; i++)
        x++;
}

