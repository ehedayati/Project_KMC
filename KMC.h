/**
 * Created by Eisa Hedayati on 
 * 10:24 AM
 * 12/2/16.
 */
//

#ifndef SC_PROJECT_CRYSTAL_GROWTH_KMC_IMP_H
#define SC_PROJECT_CRYSTAL_GROWTH_KMC_IMP_H

#include "main.h"
#include "problem_space/Surface.h"

void KMC_init(Surface *crystal_surface);
void KMC_update(Surface *crystal_surface);
void KMC_move(Surface *crystal_surface, double kmc_rand, double nu, double Bond);
void r_ei_cell_calculator(cell **p_cell, int i, int j, double nu, double Bond, int n);
void KMC_run(Surface *crystal_surface, int run_num, std::mt19937 rng, double nu, double Bond);
double KMC_height_average(Surface *pSurface);
int sing_bond(int var);
void index_search_binary(int *x, int *y, Surface *crystal_surface, double kmc_rand);

#endif //SC_PROJECT_CRYSTAL_GROWTH_KMC_IMP_H
