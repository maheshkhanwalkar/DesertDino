#include "image.h"
#include "video.h"
#include "../../lib/libg.h"

#include <stdlib.h>
#include <string.h>

/* Image structure */
struct image
{
    int row;
    int col;

    int height;
    int width;

    unsigned short* data;
};

image_t img_Create(int row, int col, int height, int width, const unsigned short* data)
{
    image_t img = malloc(sizeof(struct image));
    
    unsigned short* copy = (unsigned short*)malloc(sizeof(unsigned short) * height * width);
    memcpy(copy, data, sizeof(unsigned short) * height * width);

    img->row = row;
    img->col = col;
    img->height = height;
    img->width = width;
    img->data = copy;

    return img;
}

void img_Draw(image_t img)
{
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
        const void* src = idx_ptr(bg->data, sizeof(unsigned short), o_row, img->col, bg->width);
        void* dest = idx_ptr(bg_fill, sizeof(unsigned short), i, 0, img->width);

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

void img_Ticker(image_t img, int amt)
{
    /* no-op */
    if(amt == 0)
        return;
    
    /* Normalize amt */
    amt %= img->width;

    unsigned short* copy = malloc(sizeof(unsigned short) * img->height * img->width);

    for(int i = 0; i < img->height; i++)
    {
        int blocks = amt > 0 ? amt : -amt;

        int s1_pos = amt > 0 ? 0 : blocks;
        int d1_pos = amt > 0 ? blocks : 0;

        void* src = idx_ptr(img->data, sizeof(unsigned short), i, s1_pos, img->width);
        void* dest = idx_ptr(copy, sizeof(unsigned short), i, d1_pos, img->width);
        memcpy(dest, src, (img->width - blocks) * sizeof(unsigned short));

        int s2_pos = amt > 0 ? img->width - blocks : 0;
        int d2_pos = amt > 0 ? 0 : img->width - blocks;

        src = idx_ptr(img->data, sizeof(unsigned short), i, s2_pos, img->width);
        dest = idx_ptr(copy, sizeof(unsigned short), i, d2_pos, img->width);

        memcpy(dest, src, blocks * sizeof(unsigned short));
    }

    memcpy(img->data, copy, sizeof(unsigned short) * img->height * img->width);
    free(copy);
    
    img_Draw(img);
}

void img_Destroy(image_t img)
{
    free(img->data);
    free(img);
}

