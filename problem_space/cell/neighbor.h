/**
 * Created by Eisa Hedayati on 
 * 1:27 PM
 * 11/17/16.
 */
//

#ifndef SC_PROJECT_CRYSTAL_GROWTH_KMC_NEIGHBOR_H
#define SC_PROJECT_CRYSTAL_GROWTH_KMC_NEIGHBOR_H


#include "coordinate.h"

class neighbor {
public:
    coordinate *right,*left,*up,*down; // four nearest neighbor of an atom.
};


#endif //SC_PROJECT_CRYSTAL_GROWTH_KMC_NEIGHBOR_H
