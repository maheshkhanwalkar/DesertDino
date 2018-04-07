#include "libg.h"

#include <string.h>
#include <stdlib.h>

int idx(int row, int col, int c_max)
{
    return row * c_max + col;
}

void* idx_ptr(void* base, int e_size, int row, int col, int c_max)
{
    return (char*)base + e_size * idx(row, col, c_max);
}

/* Swap chars in a string */
static void swp(char* str, int p1, int p2)
{
    char tmp = str[p1];

    str[p1] = str[p2];
    str[p2] = tmp;
}

/* Reverse a string */
static void rev(char* str)
{
    int len = (int)strlen(str);

    for(int i = 0; i < len / 2; i++) {
        swp(str, i, len - i - 1);
    }
}

char* itoa(int num)
{
    char* data = malloc(sizeof(char) * 10);

    if(num == 0) {
        data[0] = '0';
        data[1] = '\0';

        return data;
    }

    int pos = 0;

    while(num > 0) {
        int digit = num % 10 + '0';
        data[pos++] = digit;
        num /= 10;
    }

    data[pos] = '\0';
    rev(data);

    return data;
}

