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

#include "../assets/img/cactus/cactus.h"

#include "../myLib.h"
#include "../lib/frame.h"
#include "../lib/libg.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

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
bool game_over(enum State* current);

/* Helper routine */
bool collision(image_t dino, image_t cacti);

/* Global variable: at least it's static ;) */
static bool reset = false;

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
        if(ticks == 120) {
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
                res = game_over(&current);
                break;

            default:
                break;
        }

        /* Force reset */
        if(res) {
            ticks = 0;
        }
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
        IN_AIR1,
        IN_AIR2,
        IN_AIR3,
        IN_AIR4,
        IN_AIR5,
        D_NORM0
    };

    static enum InGameStates state = D_NORM1;

    static image_t bg_ms = NULL, dino = NULL, dino_left = NULL,
        dino_right = NULL, dino_none = NULL, grd = NULL, cacti = NULL;

    const int air_amt = 25;
    const int cacti_amt = -16;

    static int score;
    static int hi_score = 0;

    /* Initialization */
    if(bg_ms == NULL || reset) {
        bg_ms = img_Create(0, 0, BG_MAIN_HEIGHT, BG_MAIN_WIDTH, bg_main);
        dino = img_Create(SCREEN_HEIGHT - DINOSAUR_HEIGHT - 1, 10, DINOSAUR_HEIGHT, DINOSAUR_WIDTH, dinosaur);
        dino_left = img_Create(SCREEN_HEIGHT - DINOSAUR_LEFT_HEIGHT - 1, 10, DINOSAUR_LEFT_HEIGHT, DINOSAUR_LEFT_WIDTH, dinosaur_left);
        dino_right = img_Create(SCREEN_HEIGHT - DINOSAUR_RIGHT_HEIGHT - 1, 10, DINOSAUR_RIGHT_HEIGHT, DINOSAUR_RIGHT_WIDTH, dinosaur_right);
        dino_none = img_Create(SCREEN_HEIGHT - DINOSAUR_NONE_HEIGHT - 1, 10, DINOSAUR_NONE_HEIGHT, DINOSAUR_NONE_WIDTH, dinosaur_none);
        grd = img_Create(SCREEN_HEIGHT - GROUND_HEIGHT, 0, GROUND_HEIGHT, GROUND_WIDTH, ground);
        cacti = img_Create(SCREEN_HEIGHT - CACTUS_HEIGHT - 5, 200, CACTUS_HEIGHT, CACTUS_WIDTH, cactus);
        score = 0;
        reset = false;
        state = D_NORM1;
    }

    /* Go back to start screen */
    if(KEY_DOWN_NOW(BUTTON_SELECT))
    {
        *current = START;

        /* Cleanup */
        img_Destroy(bg_ms);
        img_Destroy(dino);
        img_Destroy(dino_left);
        img_Destroy(dino_right);
        img_Destroy(dino_none);
        img_Destroy(grd);
        img_Destroy(cacti);

        frame_Clear(active);

        reset = true;
        return false;
    }

    if(!frame_Contains(active, bg_ms))
    {
        frame_Clear(active);

        frame_Add(active, bg_ms, true);
        frame_Draw(active, true);
    }

    /* Set jump phase */
    if(KEY_DOWN_NOW(BUTTON_UP) && state < IN_AIR1) {
        state = IN_AIR1;    
    }

    if(ticks == 100) {
        bool fail;

        /* Check fail */
        if(state > IN_AIR1) {
            fail = collision(dino_none, cacti);
        } else {
            fail = collision(dino, cacti);
        }

        /* Game over */
        if(fail) {
            *current = GAME_OVER;

            /* Cleanup */
            img_Destroy(bg_ms);
            img_Destroy(dino);
            img_Destroy(dino_left);
            img_Destroy(dino_right);
            img_Destroy(dino_none);
            img_Destroy(grd);
            img_Destroy(cacti);

            frame_Clear(active);

            return false;
        }

        /* Update high score */
        if(score > hi_score) {
            hi_score = score;
        }

        char* text = itoa(score);

        draw_str(10, 150, "SCORE:", YELLOW);
        draw_str(10, 210, text, YELLOW);

        free(text);

        text = itoa(hi_score);

        draw_str(18, 150, "HI:", YELLOW);
        draw_str(18, 210, text, YELLOW);

        free(text);

        score++;

        img_Ticker(grd, -5);

        img_Clear(cacti, bg_ms);
        img_RelMove(cacti, 0, cacti_amt);

        if(img_GetCol(cacti) < 0) {
            img_SetCol(cacti, 240);
        }

        img_Draw(cacti);

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

            case IN_AIR1:
                img_Clear(dino, bg_ms);
                img_RelMove(dino_none, -air_amt, 1);

                frame_Add(active, dino_none, false);
                frame_Draw(active, false);

                frame_Remove(active, dino_none);
                state = IN_AIR2;

                break;

            case IN_AIR2:
                img_Clear(dino_none, bg_ms);
                img_RelMove(dino_none, -air_amt, 1);

                frame_Add(active, dino_none, false);
                frame_Draw(active, false);

                frame_Remove(active, dino_none);
                state = IN_AIR3;

                break;

            case IN_AIR3:
                img_Clear(dino_none, bg_ms);
                img_RelMove(dino_none, -air_amt, 1);

                frame_Add(active, dino_none, false);
                frame_Draw(active, false);

                frame_Remove(active, dino_none);
                state = IN_AIR4;

                break;

            case IN_AIR4:
                img_Clear(dino_none, bg_ms);
                img_RelMove(dino_none, air_amt, -1);

                frame_Add(active, dino_none, false);
                frame_Draw(active, false);

                frame_Remove(active, dino_none);
                state = IN_AIR5;

                break;

            case IN_AIR5:
                img_Clear(dino_none, bg_ms);
                img_RelMove(dino_none, air_amt, -1);

                frame_Add(active, dino_none, false);
                frame_Draw(active, false);

                frame_Remove(active, dino_none);
                state = D_NORM0;

                break;

            case D_NORM0:
                img_Clear(dino_none, bg_ms);
                img_RelMove(dino_none, air_amt, -1);

                frame_Add(active, dino, false);
                frame_Draw(active, false);

                frame_Remove(active, dino);
                state = D_NORM2;
                
                break;
        }

        return true;
    }

    return false;
}

bool game_over(enum State* current)
{
    if(KEY_DOWN_NOW(BUTTON_SELECT))
    {
        *current = START;
        reset = true;

        return true;
    }
    
    draw_str(30, 80, "GAME OVER", YELLOW);
    draw_str(38, 50, "Press 'Select' to restart", YELLOW);

    return true;
}

bool collision(image_t dino, image_t cacti)
{
    int r1x2 = img_GetCol(dino) + img_GetWidth(dino);
    int r2x1 = img_GetCol(cacti);

    int r1y2 = img_GetRow(dino) + img_GetHeight(dino);
    int r2y1 = img_GetRow(cacti);

    /* There are more cases, but this will suffice */
    if(r1x2 >= r2x1 && r1y2 >= r2y1) {
        return true;
    } else {
        return false;
    }
}

