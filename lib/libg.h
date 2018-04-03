#pragma once

/**
 * Calculate 1D index given (row, col) and c_max (# of cols) 
 */
int idx(int row, int col, int c_max);

/**
 * Return pointer to element at (row, col)
 */
void* idx_ptr(void* base, int e_size, int row, int col, int c_max);

