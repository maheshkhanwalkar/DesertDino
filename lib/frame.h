#pragma once

#include <stdbool.h>
#include "../drivers/video/image.h"

struct frame;
typedef struct frame* frame_t;

/* Create a frame */
frame_t frame_Create(void);

/* Destroy the frame */
void frame_Destroy(frame_t fm);

/* Add img to frame */
void frame_Add(frame_t fm, image_t img, bool is_bg);

/* Remove img from frame */
void frame_Remove(frame_t fm, image_t img);

/* Check if frame contains img */
bool frame_Contains(frame_t fm, image_t img);

/* Get element at location 'pos' */
image_t frame_Get(frame_t fm, int pos);

/* Check if imgs is sequentially contained in the frame */
bool frame_Equals(frame_t fm, image_t* imgs, int n_size);

/* Return frame's size */
int frame_Size(frame_t fm);

/* Clear the current frame */
void frame_Clear(frame_t fm);

/* Draw the current frame (w/ a force redraw option) */
void frame_Draw(frame_t fm, bool force);

