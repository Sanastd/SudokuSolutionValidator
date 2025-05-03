#include "validator_pthread.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

int sudoku_global[9][9]; 
bool valid[11];          

typedef struct {
    int index;           
} parameters;

bool check_row(int row) {
    bool seen[10] = { false };
    for (int i = 0; i < 9; i++) {
        int num = sudoku_global[row][i];
        if (num < 1 || num > 9 || seen[num]) return false;
        seen[num] = true;
    }
    return true;
}

bool check_col(int col) {
    bool seen[10] = { false };
    for (int i = 0; i < 9; i++) {
        int num = sudoku_global[i][col];
        if (num < 1 || num > 9 || seen[num]) return false;
        seen[num] = true;
    }
    return true;
}

bool check_grid(int startRow, int startCol) {
    bool seen[10] = { false };
    for (int i = 0; i < 3; i++) 
        for (int j = 0; j < 3; j++) {
            int num = sudoku_global[startRow + i][startCol + j];
            if (num < 1 || num > 9 || seen[num]) return false;
            seen[num] = true;
        }
    return true;
}

void* validate_rows(void* arg) {
    for (int i = 0; i < 9; i++) 
        if (!check_row(i)) {
            valid[9] = false;
            return NULL;
        }
    valid[9] = true;
    return NULL;
}

void* validate_cols(void* arg) {
    for (int i = 0; i < 9; i++) 
        if (!check_col(i)) {
            valid[10] = false;
            return NULL;
        }
    valid[10] = true;
    return NULL;
}

void* validate_grid(void* arg) {
    parameters* data = (parameters*)arg;
    int idx = data->index;
    int row = (idx / 3) * 3;
    int col = (idx % 3) * 3;
    valid[idx] = check_grid(row, col);
    free(data);
    return NULL;
}

bool validate_sudoku(int sudoku[9][9]) {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            sudoku_global[i][j] = sudoku[i][j];

    pthread_t threads[11];

    pthread_create(&threads[9], NULL, validate_rows, NULL);
    pthread_create(&threads[10], NULL, validate_cols, NULL);

    for (int i = 0; i < 9; i++) {
        parameters* data = (parameters*)malloc(sizeof(parameters));
        data->index = i;
        pthread_create(&threads[i], NULL, validate_grid, data);
    }

    for (int i = 0; i < 11; i++) 
        pthread_join(threads[i], NULL);

    for (int i = 0; i < 11; i++) 
        if (!valid[i]) return false;
    
    return true;
}