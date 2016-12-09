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
void KMC_move(Surface *crystal_surface, float kmc_rand, float nu, float temp);
void r_ei_cell_calculator(cell **p_cell, int i, int j, float nu, float temp, int n);
void KMC_run(Surface *crystal_surface, int run_num, std::mt19937 rng, float nu, float temp);
void index_search_binary(int *x, int *y, Surface *crystal_surface, float kmc_rand);

#endif //SC_PROJECT_CRYSTAL_GROWTH_KMC_IMP_H
