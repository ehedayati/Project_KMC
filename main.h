/**
 * Created by Eisa Hedayati on 
 * 11:10 AM
 * 11/16/16.
 */
//

#ifndef SC_PROJECT_CRYSTAL_GROWTH_KMC_MAIN_H
#define SC_PROJECT_CRYSTAL_GROWTH_KMC_MAIN_H

//libraries
#include <iostream>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <cstdlib>
#include <cstdio>
#include <random>
#include <cstring>
#include "problem_space/cell/cell.h"
#include <boost/math/distributions/normal.hpp>
#include <boost/random.hpp>
#include <boost/generator_iterator.hpp>
#include "KMC.h"
#include "problem_space/Surface.h"
#include "problem_space/problem_space.h"

//namespaces
using namespace std;
void print_cell_mat(int rows, int columns, cell **matrix);
init_problem InitialCondition();
unsigned long long getTotalSystemMemory();
int GetRamInKB(void);

#endif //SC_PROJECT_CRYSTAL_GROWTH_KMC_MAIN_H
