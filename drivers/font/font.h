#pragma once

/**
 * Draw a character given by 'ch' at (row, col) in color 'color'
 */
void draw_char(int row, int col, char ch, unsigned short color);

/**
 * Draw a string given by 'str' at (row, col) in color 'color'
 */
void draw_str(int row, int col, const char* str, unsigned short color);

