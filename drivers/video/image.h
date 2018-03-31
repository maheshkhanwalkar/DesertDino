#pragma once

struct image;
typedef struct image* image_t;

/* Create an image */
image_t img_Create(int row, int col, int height, int width, const unsigned short* data);

/* Draw the provided image */
void img_Draw(image_t img);

/* Clear img from the screen (background fill) */
void img_Clear(image_t img, image_t bg);

/* Destroy the image */
void img_Destroy(image_t ptr);

