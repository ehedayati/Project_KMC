#include "main.h"




int main() {
    std::mt19937 rng;
    rng.seed(seeder());
    //initialization conditions
    int n = 64;

    double nu = 1.;
    double temp = .3;
    double bond = -1./temp;
    double d_mu = 5/temp;
    int step_num = 100000;

    //initializing surface
    Surface *crystal = new Surface();
    crystal->n = n;
    surface_init(d_mu, nu, bond, crystal);

    // get surface ready for KMC Method
    KMC_init(crystal);

// average z on time. done.

    //Run simulation
    KMC_run(crystal, step_num, rng, nu, bond);


    cout << endl;

    double tot = 0.;
    for (int i = 0; i < n ; ++i) {
        for (int j = 0; j < n; ++j) {
            tot+= crystal->cells[i][j].h;
//            printf("%d\t",crystal->cells[i][j].h);
        }
        cout << endl;
    }
cout << tot/(n*n);

    free(crystal);
//    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");


    return 0;
}







