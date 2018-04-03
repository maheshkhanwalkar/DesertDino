
int idx(int row, int col, int c_max)
{
    return row * c_max + col;
}

void* idx_ptr(void* base, int e_size, int row, int col, int c_max)
{
    return (char*)base + e_size * idx(row, col, c_max);
}

