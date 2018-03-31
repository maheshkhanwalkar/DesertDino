#include "image.h"
#include "video.h"

#include <stdlib.h>
#include <string.h>

/* Image structure */
struct image
{
    int row;
    int col;

    int height;
    int width;

    const unsigned short* data;
};

/* Compute address */
static inline void* addr(const void* base, int e_size, int row, int col, int c_count)
{
    return (char*)base + e_size * (row * c_count + col);
}

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

void img_Clear(image_t img, image_t bg)
{
    /* Allocate buffer */
    unsigned short* bg_fill = malloc(sizeof(unsigned short) * img->height * img->width);
    int o_row = img->row; 

    /* Extract the required pixels */
    for(int i = 0; i < img->height; i++) 
    {
        const void* src = addr(bg->data, sizeof(unsigned short), o_row, img->col, bg->width);
        void* dest = addr(bg_fill, sizeof(unsigned short), i, 0, img->width);

        memcpy(dest, src, sizeof(unsigned short) * img->width);
        o_row++;
    }

    /* Draw the image */
    image_t clr = img_Create(img->row, img->col, img->height, img->width, bg_fill);
    img_Draw(clr);

    /* Cleanup */
    free(bg_fill);
    img_Destroy(clr);
}

void img_Destroy(image_t img)
{
    /* Invalid ptr */
    if(!img)
        return;

    free(img);
}

