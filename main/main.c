/* main.c: entry point of the game */

#include "../drivers/video/video.h"
#include "../drivers/video/image.h"
#include "../drivers/font/font.h"

#include "../assets/img/dino/dinosaur.h"
#include "../assets/img/dino/dinosaur_left.h"
#include "../assets/img/dino/dinosaur_right.h"

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
void in_game(image_t* bg[3], enum State* current, bool* rs);

void do_rs(enum State* state, bool* c1, bool* c2);


int main(void)
{
    init_mode3();

    /* Create image objects */
    image_t bg_title = img_Create(0, 0, BG_DARK_HEIGHT, BG_DARK_WIDTH, bg_dark);
    image_t bg_ms = img_Create(0, 0, BG_MAIN_HEIGHT, BG_MAIN_WIDTH, bg_main);

    image_t dino = img_Create(SCREEN_HEIGHT - DINOSAUR_HEIGHT - 1, 10, DINOSAUR_HEIGHT, DINOSAUR_WIDTH, dinosaur);
    image_t dino_left = img_Create(SCREEN_HEIGHT - DINOSAUR_LEFT_HEIGHT - 1, 10, DINOSAUR_LEFT_HEIGHT, DINOSAUR_LEFT_WIDTH, dinosaur_left);
    image_t dino_right = img_Create(SCREEN_HEIGHT - DINOSAUR_RIGHT_HEIGHT - 1, 10, DINOSAUR_RIGHT_HEIGHT, DINOSAUR_RIGHT_WIDTH, dinosaur_right);

    image_t grd = img_Create(SCREEN_HEIGHT - GROUND_HEIGHT, 0, GROUND_HEIGHT, GROUND_WIDTH, ground);
    image_t* imgs[3] = { &dino, &dino, &grd };

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
                    imgs[1] = &dino;
                    which++;
                } else if(which == 0) {
                    imgs[1] = &dino_left;
                    which++;
                } else if(which == 1) {
                    imgs[1] = &dino;
                    which++;
                } else {
                    imgs[1] = &dino_right;
                    which = -1;
                }
  
                in_game(imgs, &current, &restart);

                if(restart){
                    do_rs(&current, &s_once, &g_once);
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
void in_game(image_t* imgs[3], enum State* current, bool* restart)
{
    /* Get images */
    image_t* dino = imgs[0];
    image_t* grd = imgs[2];

    if(KEY_DOWN_NOW(BUTTON_SELECT))
    {
        *restart = true;
        *current = START;

        return;
    }

    img_Ticker(*grd, -5);
    img_Draw(*dino);

    delay(20);

    *current = IN_GAME;
}

/* Reset variables (on restart) */
void do_rs(enum State* state, bool* c1, bool* c2)
{
    *state = START;
    *c1 = false;
    *c2 = false;
}

void delay(int n)
{
    volatile int x = 0;

    for(int i = 0; i < n * 8000; i++)
        x++;
}

