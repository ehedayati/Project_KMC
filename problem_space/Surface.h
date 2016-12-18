/**
 * Created by Eisa Hedayati on 
 * 1:31 PM
 * 11/17/16.
 */
//

#ifndef SC_PROJECT_CRYSTAL_GROWTH_KMC_SURFACE_H
#define SC_PROJECT_CRYSTAL_GROWTH_KMC_SURFACE_H

#include "cell/cell.h"

struct Surface {
    int n;
    cell **cells;
    double r_a_sum;
    double r_ei_sum;
};

struct init_problem {
    int n;
    double bond;
    double d_mu;
    int sweep;
};

#endif //SC_PROJECT_CRYSTAL_GROWTH_KMC_SURFACE_H
