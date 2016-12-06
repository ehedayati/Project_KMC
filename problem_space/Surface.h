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
    float r_a_sum;
    float r_ei_sum;
};


#endif //SC_PROJECT_CRYSTAL_GROWTH_KMC_SURFACE_H
