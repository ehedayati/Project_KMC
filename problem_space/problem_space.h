/**
 * Created by Eisa Hedayati on 
 * 12:23 PM
 * 11/16/16.
 */
//

#ifndef SC_PORJECT_CRYSTAL_GROWTH_KMC_PROBLEM_SPACE_H
#define SC_PORJECT_CRYSTAL_GROWTH_KMC_PROBLEM_SPACE_H

#include "../main.h"

void r_adatom_evap_init(Surface *p_surface, float d_mu, float nu, float Temp);
void surface_init(float d_mu, float nu, float Temp, Surface *crystal_surface);
unsigned int seeder();


#endif //SC_PORJECT_CRYSTAL_GROWTH_KMC_PROBLEM_SPACE_H
