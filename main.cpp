#include "main.h"

int main() {
    std::mt19937 rng;
    rng.seed(seeder());
    //returns available memory to use
    cout << GetRamInKB() << endl;
    double nu = 1.;
//    double temp = 1;
    init_problem initialization;
init:
    try {
        initialization = InitialCondition();
    } catch (int e)
    {
        cout << "I was not able to find 'initialization_data' to read the initialized data" << endl;
        cout << "please enter 'r' to retry or any other key to exit: ";
        char input[100];
        cin >> input;
        if (input[0] == 'r' || input[0] == 'R')
            goto init;
        else
            return 0;
    }

    int n = initialization.n;
    double bond = initialization.bond;
    double d_mu = initialization.d_mu;
    int step_num = initialization.sweep*n*n;
//    double bond = -9.2;
//    double d_mu = 9;
//    int step_num = 100*n*n;

    //initializing surface
    Surface *crystal = new Surface();
    crystal->n = n;
    surface_init(d_mu, nu, bond, crystal);

    // get surface ready for KMC Method
    KMC_init(crystal);


    //Run simulation
    KMC_run(crystal, step_num, rng, nu, bond);


    cout << endl;

    double tot = 0.;
    for (int i = 0; i < n ; ++i) {
        for (int j = 0; j < n; ++j) {
            tot+= crystal->cells[i][j].h;
//            printf("%lg\t",crystal->cells[i][j].r_a);
        }
//        cout << endl;
    }
    cout << tot/(n*n);

    free(crystal);
//    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");


    return 0;
}








