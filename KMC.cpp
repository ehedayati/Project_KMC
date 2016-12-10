/**
 * Created by Eisa Hedayati on 
 * 10:24 AM
 * 12/2/16.
 */
//

#include "KMC.h"

void KMC_init(Surface *crystal_surface) {

    double r_a = 0;
    double r_ei = 0;

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


void KMC_update(Surface *crystal_surface) {

    double r_ei_cu_old = 0;

    int n = crystal_surface->n;
    for (int i = 0; i < n  ; ++i) {
        for (int j = 0; j < n; ++j) {
            crystal_surface->cells[i][j].cumulative_r_ei_index = r_ei_cu_old;
            r_ei_cu_old +=crystal_surface->cells[i][j].r_ei;
        }
    }
    crystal_surface->r_ei_sum = r_ei_cu_old;

}


void index_search_binary(int *x, int *y, Surface *crystal_surface, double kmc_rand) {
    int index;
    int n = crystal_surface->n;
    double  r_a_sum = crystal_surface->r_a_sum;
    double r_ei_sum  = crystal_surface->r_ei_sum;

    if (kmc_rand > r_ei_sum) {
        index = (int) (((kmc_rand - r_ei_sum) * n*n) / r_a_sum);
        *x = (index/n);
        *y = (index % n);
        if (*x >= n)
            *x =n-1;
        if (*y >= n)
            *y =n-1;

        if (*y == -1)
            exit(20);
        return;
    }

    int i, j;
    int first,last, middle;

    index = n*n;

    first = 0;
    last = index-1;

    while (1) {
        middle = (last + first) / 2;
        i = middle / n;
        j = (middle % n);
        if (i ==n)
            exit(16);
        if (i ==n)
            exit(15);
        double cumulative = crystal_surface->cells[i][j].cumulative_r_ei_index;

        if (cumulative < kmc_rand) {
            if (( cumulative + crystal_surface->cells[i][j].r_ei) >= kmc_rand)
                break;
            else
                first = middle + 1;
        } else
            last = middle - 1;

    }

    *x = i;
    *y = j;
}

void KMC_move(Surface *crystal_surface, double kmc_rand, double nu, double Bond) {

    int x,y;
    int n = crystal_surface->n;

    index_search_binary(&x, &y, crystal_surface, kmc_rand);

    if (kmc_rand <= crystal_surface->r_ei_sum)
        crystal_surface->cells[x][y].h --;
    else
        crystal_surface->cells[x][y].h ++;

    //changing r_ei for cell
    crystal_surface->r_ei_sum -= crystal_surface->cells[x][y].r_ei;
    r_ei_cell_calculator(crystal_surface->cells, x, y , nu, Bond, n);

    crystal_surface->r_ei_sum += crystal_surface->cells[x][y].r_ei;


    // periodic boundary condition set up

    //changing r_ei for the next and prev to x
    int next = x+1;
    int prev = x-1;
    if (next == n)
        next = 0;
    if (x == 0)
        prev = n-1;

//    crystal_surface->r_ei_sum -= crystal_surface->cells[next][y].r_ei;
    r_ei_cell_calculator(crystal_surface->cells, next, y, nu, Bond, n);
//    crystal_surface->r_ei_sum += crystal_surface->cells[next][y].r_ei;

//    crystal_surface->r_ei_sum -= crystal_surface->cells[prev][y].r_ei;
    r_ei_cell_calculator(crystal_surface->cells, prev, y, nu, Bond, n);
//    crystal_surface->r_ei_sum += crystal_surface->cells[prev][y].r_ei;

    //changing r_ei for the next and prev to y
    next = y+1;
    prev = y-1;
    if (next == n)
        next = 0;
    if (y == 0)
        prev = n-1;

//    crystal_surface->r_ei_sum -= crystal_surface->cells[x][next].r_ei;
    r_ei_cell_calculator(crystal_surface->cells, x, next, nu, Bond, n);
//    crystal_surface->r_ei_sum += crystal_surface->cells[x][next].r_ei;

//    crystal_surface->r_ei_sum -= crystal_surface->cells[x][prev].r_ei;
    r_ei_cell_calculator(crystal_surface->cells, x, prev, nu, Bond, n);
//    crystal_surface->r_ei_sum += crystal_surface->cells[x][prev].r_ei;
    //updating the cumulative indexes
    KMC_update(crystal_surface);
}

void r_ei_cell_calculator(cell **p_cell, int i, int j, double nu, double Bond, int n) {
    int delta_E;
    //periodic boundary condition:
    int next = i+1;
    int prev = i-1;
    if (next == n)
        next = 0;
    if (i == 0)
        prev = n-1;
    //p.4 ch.5

    delta_E = 1
              + sing_bond(p_cell[i][j].h - p_cell[next][j].h)
              + sing_bond(p_cell[i][j].h - p_cell[prev][j].h);

    next = j+1;
    prev = j-1;
    if (next == n)
        next = 0;
    if (j == 0)
        prev = n-1;

    delta_E = delta_E
              + sing_bond(p_cell[i][j].h - p_cell[i][next].h)
              + sing_bond(p_cell[i][j].h - p_cell[i][prev].h);
//    FILE *f_write = fopen("delta_E", "a");
//    fprintf(f_write, "%d\n",delta_E);
//    fclose(f_write);
    p_cell[i][j].r_ei =  (nu * exp((delta_E) * Bond));
}

void KMC_run(Surface *crystal_surface, int run_num, std::mt19937 rng, double nu, double Bond) {


    //calculating the limits for generating random numbers
    int n = crystal_surface->n;
    double limit;
    int print_step = n*n;
    int timestep = 0;
    //print to file--uncomment for file generation

    FILE *f_write = fopen("Datafile", "w");
    fprintf(f_write, "# Height matrix\n");
    fclose(f_write);

    f_write = fopen("Height_average", "w");
    fprintf(f_write, "# Height average\n");



    print_cell_mat(n,n,crystal_surface->cells);

    std::uniform_int_distribution<int> int_gen(0, n-1);
    fprintf(f_write, "%d\t%lg\n",timestep, KMC_height_average(crystal_surface));
    //running the KMC steps.
    int print_count = 0;
    for (int i = 0; i < run_num; ++i) {
        limit = crystal_surface->r_a_sum + crystal_surface->r_ei_sum;
        std::uniform_real_distribution<double> real_gen(0,limit);
        print_count++;

        double kmc_rand = real_gen(rng);
        KMC_move(crystal_surface, kmc_rand, nu, Bond);
        //uncomment for file generation
        if (print_count == print_step){
            timestep++;
            fprintf(f_write, "%d\t%lg\n",timestep, KMC_height_average(crystal_surface));
            print_count = 0;
            print_cell_mat(n,n,crystal_surface->cells);
        }
    }

    fclose(f_write);
}

double KMC_height_average(Surface *pSurface) {
    double sum = 0;
    for (int i = 0; i < pSurface->n; ++i) {
        for (int j = 0; j < pSurface->n; ++j) {
            sum +=pSurface->cells[i][j].h;
        }
    }
    return sum/(pSurface->n*pSurface->n);
}

int sing_bond(int var) {

    if (var <= 0)
        return 1;
    else //if (var > 0)
        return 0;
//    else
//        return 0;
}
