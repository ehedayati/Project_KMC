/**
 * Created by Eisa Hedayati on 
 * 1:12 PM
 * 12/5/16.
 */
//

#include "main.h"

void print_cell_mat(int rows, int columns, cell **matrix) {

    FILE *f_write = fopen("visualization/.Datafile.xyz", "a");
    fprintf(f_write, "%d\n\n",rows*columns);

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            fprintf(f_write, "S %d %d %d\t\n",r,c,matrix[r][c].h);
        }
    }

    fclose(f_write);
}

init_problem InitialCondition() {
    FILE *init_read = fopen("initialization_data", "r");;
    if(init_read == NULL)
        throw 21;

    init_problem initialization = init_problem();
    char line[256];
    while(fgets(line, sizeof(line), init_read))
    {
        int n;
        if(sscanf(line, "n: %d", &n) == 1)
        {
            initialization.n = n;
            break;
        } else
            throw 50;
    }

    while(fgets(line, sizeof(line), init_read))
    {
        double bond;
        if(sscanf(line, "Bond: %lf", &bond) == 1)
        {
            initialization.bond = bond;
            break;
        } else
            throw 50;
    }

    while(fgets(line, sizeof(line), init_read))
    {
        double d_mu;
        if(sscanf(line, "Delta_mu: %lf", &d_mu) == 1)
        {
            initialization.d_mu = d_mu;
            break;
        } else
            throw 50;
    }

    while(fgets(line, sizeof(line), init_read))
    {
        int sweep;
        if(sscanf(line, "Sweep: %d", &sweep) == 1)
        {
            initialization.sweep = sweep;
            break;
        } else
            throw 50;
    }
    fclose(init_read);
    return initialization;
}