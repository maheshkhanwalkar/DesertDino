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
#include "../lib/frame.h"

#include <stdbool.h>
#include <stddef.h>

/* Game states */
enum State
{
    START,
    IN_GAME,
    GAME_OVER,
};

/* Game state handling functions */
bool title_screen(frame_t active, enum State* current);
bool in_game(frame_t active, int ticks, enum State* current);

int main(void)
{
    init_mode3();

    /* Starting state */
    enum State current = START;
    frame_t active = frame_Create();

    int ticks = 0;

    while(1) 
    {
        waitForVBlank();
        ticks++;

        /* Reset */
        if(ticks == 60) {
            ticks = 0;
        }

        /* Potential updates */
        bool res = false;

        switch(current)
        {
            case START:
                res = title_screen(active, &current);
                break;

            case IN_GAME:
                res = in_game(active, ticks, &current);
                break;

            case GAME_OVER:
                break;

            default:
                break;
        }

        /* Force reset */
        if(res) {
            ticks = 0;
        }

}

/* Display title screen */
bool title_screen(frame_t active, enum State* state)
{
    /* Title image */
    static image_t img = NULL;
   
    /* Initialization */
    if(img == NULL) {
        img = img_Create(0, 0, BG_DARK_HEIGHT, BG_DARK_WIDTH, bg_dark);
    }

    /* Start game */
    if(KEY_DOWN_NOW(BUTTON_START))
    {
        *state = IN_GAME;
        return false;
    }

    /* No updates */
    if(frame_Equals(active, &img, 1))
        return false;

    frame_Clear(active);
    frame_Add(active, img, true);

    frame_Draw(active, true);

    draw_str(5, 80, "Desert Dino", YELLOW);
    draw_str(25, 50, "Press 'Start' to Begin", YELLOW);

    return true;
}

bool in_game(frame_t active, int ticks, enum State* current)
{
    // In-game states 
    enum InGameStates {
        D_NORM1,
        D_NORM2,
        D_LEFT,
        D_RIGHT,
    };

    static enum InGameStates state = D_NORM1;

    static image_t bg_ms = NULL, dino = NULL, dino_left = NULL,
        dino_right = NULL, dino_none = NULL, grd = NULL;

    /* Initialization */
    if(bg_ms == NULL) {
        bg_ms = img_Create(0, 0, BG_MAIN_HEIGHT, BG_MAIN_WIDTH, bg_main);
        dino = img_Create(SCREEN_HEIGHT - DINOSAUR_HEIGHT - 1, 10, DINOSAUR_HEIGHT, DINOSAUR_WIDTH, dinosaur);
        dino_left = img_Create(SCREEN_HEIGHT - DINOSAUR_LEFT_HEIGHT - 1, 10, DINOSAUR_LEFT_HEIGHT, DINOSAUR_LEFT_WIDTH, dinosaur_left);
        dino_right = img_Create(SCREEN_HEIGHT - DINOSAUR_RIGHT_HEIGHT - 1, 10, DINOSAUR_RIGHT_HEIGHT, DINOSAUR_RIGHT_WIDTH, dinosaur_right);
        dino_none = img_Create(SCREEN_HEIGHT - DINOSAUR_NONE_HEIGHT - 1, 10, DINOSAUR_NONE_HEIGHT, DINOSAUR_NONE_WIDTH, dinosaur_none);
        grd = img_Create(SCREEN_HEIGHT - GROUND_HEIGHT, 0, GROUND_HEIGHT, GROUND_WIDTH, ground);
    }

    (void)dino_none;

    /* Go back to start screen */
    if(KEY_DOWN_NOW(BUTTON_SELECT))
    {
        *current = START;
        return false;
    }

    if(!frame_Contains(active, bg_ms))
    {
        frame_Clear(active);

        frame_Add(active, bg_ms, true);
        frame_Draw(active, true);
    }

    if(ticks == 30) {
        img_Ticker(grd, -5);
        
        switch(state) 
        {
            case D_NORM1:
                frame_Add(active, dino, false);
                frame_Draw(active, false); 
                frame_Remove(active, dino);
                state = D_LEFT;

                break;

            case D_LEFT:
                frame_Add(active, dino_left, false);
                frame_Draw(active, false);
                frame_Remove(active, dino_left);
                state = D_NORM2;

                break;

            case D_NORM2:
                frame_Add(active, dino, false);
                frame_Draw(active, false);
                frame_Remove(active, dino);
                state = D_RIGHT;

                break;

            case D_RIGHT:
                frame_Add(active, dino_right, false);
                frame_Draw(active, false);
                frame_Remove(active, dino_right);
                state = D_NORM1;

                break;
        }

        return true;
    }

    return false;
}

/* Render in-game content */
/*void in_game(image_t imgs[4], enum State* current, bool* restart)
{
    static bool in_air = false;
    static int ticks = 0;

    image_t dino = imgs[0];
    image_t dino_none = imgs[1];
    image_t grd = imgs[2];
    image_t bg = imgs[3];

    //frame_t active = frame_Create(NULL, 0); 

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
        if(ticks < 30) 
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

    *current = IN_GAME;
    delay(20);
}

