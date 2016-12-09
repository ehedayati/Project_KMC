/**
 * Created by Eisa Hedayati on 
 * 12:36 PM
 * 11/16/16.
 */
//

#ifndef SC_PROJECT_CRYSTAL_GROWTH_KMC_CELL_H
#define SC_PROJECT_CRYSTAL_GROWTH_KMC_CELL_H

#include "coordinate.h"
#include "neighbor.h"

struct cell{
    float r_a; //hamiltonian of SOS method
    float r_ei; //hamiltonian of DG method
    int h;// cell height
    float cumulative_r_ei_index;
};


#endif //SC_PORJECT_CRYSTAL_GROWTH_KMC_CELL_H
