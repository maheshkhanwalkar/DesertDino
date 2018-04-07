#pragma once

struct image;
typedef struct image* image_t;

/* Create an image */
image_t img_Create(int row, int col, int height, int width, const unsigned short* data);

/* Draw the provided image */
void img_Draw(image_t img);

/* Clear img from the screen (background fill) */
void img_Clear(image_t img, image_t bg);

/* Move img by (r_amt, c_amt) */
void img_RelMove(image_t img, int r_amt, int c_amt);

/* Get column position */
int img_GetCol(image_t img);

/* Set column position to col */
void img_SetCol(image_t img, int col);

/* Move image ticker by 'amt' (wrap around) and stores the new image in 'img' */
void img_Ticker(image_t img, int amt);

/* Destroy the image */
void img_Destroy(image_t ptr);

