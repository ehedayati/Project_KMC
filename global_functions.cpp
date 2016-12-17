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

init_problem InitialCondition() {
    FILE *init_read = fopen("initialization_data", "r");;
    if(init_read == NULL)
        throw 21;

    init_problem initialization;
    char line[256];
    while(fgets(line, sizeof(line), init_read))
    {
        double bond;
        if(sscanf(line, "Bond: %lf kB", &bond) == 1)
        {
            initialization.bond = bond;
            break;
        }
    }

    while(fgets(line, sizeof(line), init_read))
    {
        double d_mu;
        if(sscanf(line, "Delta_mu: %lf kB", &d_mu) == 1)
        {
            initialization.d_mu = d_mu;
            break;
        }
    }

    while(fgets(line, sizeof(line), init_read))
    {
        int sweep;
        if(sscanf(line, "Sweep: %d kB", &sweep) == 1)
        {
            initialization.sweep = sweep;
            break;
        }
    }
    fclose(init_read);
    return initialization;
}