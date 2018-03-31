#include "image.h"
#include "video.h"

#include <stdlib.h>

/* Image structure */
struct image
{
    int row;
    int col;

    int height;
    int width;

    const unsigned short* data;
};

image_t img_Create(int row, int col, int height, int width, const unsigned short* data)
{
    image_t img = malloc(sizeof(struct image));

    img->row = row;
    img->col = col;
    img->height = height;
    img->width = width;
    img->data = data;

    return img;
}

void img_Draw(image_t img)
{
    if(!img)
        return;

    /* Actually draw the image */
    draw_img(img->row, img->col, img->height, img->width, img->data);
}

void img_Destroy(image_t img)
{
    /* Invalid ptr */
    if(!img)
        return;

    free(img);
}

