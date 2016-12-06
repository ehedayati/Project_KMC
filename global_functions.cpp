/**
 * Created by Eisa Hedayati on 
 * 1:12 PM
 * 12/5/16.
 */
//

#include "main.h"

void print_cell_mat(int rows, int columns, cell **matrix) {

    FILE *f_write = fopen("Datafile", "a");
    fprintf(f_write, "\n\n");

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            fprintf(f_write, "%d\t",matrix[r][c].h);
        }
        fprintf(f_write,"\n");
    }

    fclose(f_write);
}
