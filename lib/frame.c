#include "frame.h"

#include <stdlib.h>
#include <stdbool.h>

/* Frame Node */
struct f_node
{
    image_t data;
    bool update, bg;

    struct f_node* next;
};

struct frame
{
    struct f_node* head;
    int size;
};

frame_t frame_Create(void)
{
    frame_t fm = malloc(sizeof(struct frame));

    fm->head = NULL;
    fm->size = 0;

    return fm;
}

void frame_Add(frame_t fm, image_t img, bool is_bg)
{
    struct f_node* item = malloc(sizeof(struct f_node));
    
    item->data = img;
    item->next = fm->head;
    item->update = false;
    item->bg = is_bg;

    fm->head = item;
    fm->size++;
}

void frame_Remove(frame_t fm, image_t img)
{
    struct f_node* curr = fm->head;
    struct f_node* prev = curr;

    while(curr != NULL) {
        if(curr->data == img) {

            if(curr == fm->head) {
                fm->head = curr->next;
                fm->size--;

                free(curr);
                return;
            }

            prev->next = curr->next;
            fm->size--;

            free(curr);
            return;
        }

        prev = curr;
        curr = curr->next;
    }
}

bool frame_Contains(frame_t fm, image_t img)
{
    struct f_node* curr = fm->head;

    while(curr != NULL) {
        if(curr->data == img)
            return true;

        curr = curr->next;
    }

    return false;
}

image_t frame_Get(frame_t fm, int pos)
{
    if(pos >= fm->size) {
        return NULL;
    }

    struct f_node* curr = fm->head;

    while(pos > 0) {
        curr = curr->next;
    }

    return curr->data;
}

bool frame_Equals(frame_t fm, image_t* imgs, int n_size)
{
    if(n_size != fm->size)
        return false;

    struct f_node* curr = fm->head;
    int i = 0;

    while(curr != NULL) {
        if(curr->data != imgs[i])
            return false;

        curr = curr->next;
        i++;
    }

    return true;
}

void frame_Clear(frame_t fm)
{
    /* Remove all items */
    while(fm->size > 0) {
        frame_Remove(fm, fm->head->data);
    }
}

int frame_Size(frame_t fm)
{
    return fm->size;
}

void frame_Draw(frame_t fm, bool force)
{
    struct f_node* curr = fm->head;

    while(curr != NULL) {

        if(!curr->update || force || !curr->bg) {
            img_Draw(curr->data);
            curr->update = true;
        }

        curr = curr->next;
    }
}

void frame_Destroy(frame_t fm)
{
    frame_Clear(fm);
    free(fm);
}

