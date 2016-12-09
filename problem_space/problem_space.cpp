/**
 * Created by Eisa Hedayati on 
 * 12:23 PM
 * 11/16/16.
 */
//

#include "problem_space.h"

//periodic init
void r_adatom_evap_init(Surface *p_surface, double d_mu, double nu, double Bond) {

    cell **p_crystal_cells;
    p_crystal_cells = p_surface->cells;
    int n = p_surface->n;

    int next_i,next_j;
    int prev_i,prev_j;
    double r_ei_cu_old = 0;
    p_crystal_cells[0][0].cumulative_r_ei_index = 0;
    //everywhere but boundaries
    for (int i = 0; i < n; ++i) {
        //neighbours of i

//        next_i = i+1;//use mod for periodic, Minimum image condition
//        prev_i = i-1;
//        if (next_i == n)
//            next_i = 0;
//        if (i == 0)
//            prev_i = n-1;
        for (int j = 0; j < n; ++j) {
//            // neighbours of j
//            next_j = j+1;
//            prev_j = j-1;
//            if (next_j == n)
//                next_j = 0;
//            if (j == 0)
//                prev_j = n-1;

            double ra = (nu * exp(3*Bond) * exp(d_mu));
            p_crystal_cells[i][j].r_a = ra;

            r_ei_cell_calculator(p_crystal_cells,i,j,nu,Bond,n);
//            p_crystal_cells[i][j].r_ei = (nu * exp((delta_E)*Bond));
            p_crystal_cells[i][j].cumulative_r_ei_index = r_ei_cu_old;
            r_ei_cu_old +=p_crystal_cells[i][j].r_ei;
        }
    }

}


void surface_init(double d_mu, double nu, double Temp, Surface *crystal_surface) {
    //initializing the random number generator, using mersenne_twister_engine

    int n = crystal_surface->n;

    cell **crystal_cells;
    crystal_cells = new cell*[n];
    for (int i = 0; i < n; ++i) {
        crystal_cells[i] = new cell[n];
    }

    cell empty;
    empty.h = 0;
    empty.r_a = 0;
    empty.r_ei = 0;
    empty.cumulative_r_ei_index = 0;

    for (int i = 0; i < n ; ++i) {
        for (int j = 0; j < n; ++j) {
            crystal_cells[i][j] = empty;
        }
    }

    crystal_surface->cells = crystal_cells;

    // find the initial values for adatom and evaporation factor
    r_adatom_evap_init(crystal_surface, d_mu, nu, Temp);

    // uncomment for printing the initial condition
//
//    for (int i = 0; i < n ; ++i) {
//        for (int j = 0; j < n; ++j) {
//            printf("%lg,%lg\t",crystal_cells[i][j].r_ei,crystal_cells[i][j].cumulative_r_ei_index);
//        }
//        cout << endl;
//    }
}


unsigned int seeder() {
    FILE *urandom;
    unsigned int seed;
    urandom = fopen("/dev/urandom", "r");
    if (urandom == NULL) {
        fprintf(stderr, "Cannot open /dev/urandom!\n");
        exit(1);
    }
    fread(&seed, sizeof(seed), 1, urandom);

    fclose(urandom);
    return seed;
}