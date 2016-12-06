/**
 * Created by Eisa Hedayati on 
 * 10:24 AM
 * 12/2/16.
 */
//

#include "KMC.h"

void KMC_init(Surface *crystal_surface) {

    float r_a = 0;
    float r_ei = 0;

    int n = crystal_surface->n;
    for (int i = 0; i < n  ; ++i) {
        for (int j = 0; j < n; ++j) {
            r_a +=crystal_surface->cells[i][j].r_a;
            r_ei +=crystal_surface->cells[i][j].r_ei;
        }
    }

    crystal_surface->r_a_sum = r_a;
    crystal_surface->r_ei_sum = r_ei;
}

void KMC_move(Surface *crystal_surface, int x, int y, float kmc_rand, float nu, float temp) {

    int n = crystal_surface->n;

    if (kmc_rand <= crystal_surface->r_ei_sum)
        crystal_surface->cells[x][y].h --;
    else
        crystal_surface->cells[x][y].h ++;

    //changing r_ei for cell
    crystal_surface->r_ei_sum -= crystal_surface->cells[x][y].r_ei;
    r_ei_cell_calculator(crystal_surface->cells, x, y , nu, temp, n);
    crystal_surface->r_ei_sum += crystal_surface->cells[x][y].r_ei;


    // periodic boundary condition set up

    //changing r_ei for the next and prev to x
    int next = x+1;
    int prev = x-1;
    if (next == n)
        next = 0;
    if (x == 0)
        prev = n-1;
    crystal_surface->r_ei_sum -= crystal_surface->cells[next][y].r_ei;
    r_ei_cell_calculator(crystal_surface->cells, next, y, nu, temp, n);
    crystal_surface->r_ei_sum += crystal_surface->cells[next][y].r_ei;

    crystal_surface->r_ei_sum -= crystal_surface->cells[prev][y].r_ei;
    r_ei_cell_calculator(crystal_surface->cells, prev, y, nu, temp, n);
    crystal_surface->r_ei_sum += crystal_surface->cells[prev][y].r_ei;

    //changing r_ei for the next and prev to y
    next = y+1;
    prev = y-1;
    if (next == n)
        next = 0;
    if (y == 0)
        prev = n-1;
    crystal_surface->r_ei_sum -= crystal_surface->cells[x][next].r_ei;
    r_ei_cell_calculator(crystal_surface->cells, x, next, nu, temp, n);
    crystal_surface->r_ei_sum += crystal_surface->cells[x][next].r_ei;

    crystal_surface->r_ei_sum -= crystal_surface->cells[x][prev].r_ei;
    r_ei_cell_calculator(crystal_surface->cells, x, prev, nu, temp, n);
    crystal_surface->r_ei_sum += crystal_surface->cells[x][prev].r_ei;
}

void r_ei_cell_calculator(cell **p_cell, int i, int j, float nu, float temp, int n) {

    //periodic boundary condition:
    int next = i+1;
    int prev = i-1;
    if (next == n)
        next = 0;
    if (i == 0)
        prev = n-1;

    float D_E_i = abs(p_cell[i][j].h - 1 - p_cell[next][j].h) + abs(p_cell[i][j].h - 1 - p_cell[prev][j].h);

    next = j+1;
    prev = j-1;
    if (next == n)
        next = 0;
    if (j == 0)
        prev = n-1;

    float D_E_j = abs(p_cell[i][j].h - 1 - p_cell[i][next].h) + abs(p_cell[i][j].h - 1 - p_cell[i][prev].h);

    p_cell[i][j].r_ei = (float) (nu * exp(-.5 * (D_E_i + D_E_j) * temp));
}

void KMC_run(Surface *crystal_surface, int run_num, std::mt19937 rng, float nu, float temp) {

    int print_step = 1;
    //calculating the limits for generating random numbers
    int n = crystal_surface->n;
    float limit = crystal_surface->r_a_sum + crystal_surface->r_ei_sum;

    //print to file--uncomment for file generation

    FILE *f_write = fopen("Datafile", "w");
    fprintf(f_write, "# Height matrix\n");
    fclose(f_write);


    print_cell_mat(n,n,crystal_surface->cells);

    std::uniform_int_distribution<int> int_gen(0, n-1);
    std::uniform_real_distribution<float> real_gen(0,limit);

    //running the KMC steps.
    int print_count = 0;
    for (int i = 0; i < run_num; ++i) {
        print_count++;
        int x = int_gen(rng);
        int y = int_gen(rng);
        float kmc_rand = real_gen(rng);
        KMC_move(crystal_surface,x,y,kmc_rand,nu,temp);
        //uncomment for file generation
        if (print_count == print_step){
            print_count =0;
            print_cell_mat(n,n,crystal_surface->cells);
        }
    }


}
