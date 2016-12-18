#include "main.h"

int main() {
    std::mt19937 rng;
    rng.seed(seeder());
    //returns available memory to use
//    cout << GetRamInKB() << endl;
    double nu = 1.;
//    double temp = 1;
    init_problem initialization;
init:
    try {
        initialization = InitialCondition();
    } catch (int e) {
        if (e == 21) {
            cout << "I was not able to find 'initialization_data' to read the initialized data" << endl;
            cout << "please enter 'r' to retry or any other key to exit: ";
            char input[100];
            cin >> input;
            if (input[0] == 'r' || input[0] == 'R')
                goto init;
            else
                return 0;
        }
        if (e ==50) {
            cout << "The data file syntax is not correct" << endl;
            cout << "please enter 'r' to retry or any other key to exit: ";
            char input[100];
            cin >> input;
            if (input[0] == 'r' || input[0] == 'R')
                goto init;
            else
                return 0;
        }
    }

    int n = initialization.n;
    double bond = initialization.bond;
    double d_mu = initialization.d_mu;
    int step_num = initialization.sweep*n*n;

    //initializing surface
    Surface *crystal = new Surface();
    crystal->n = n;
    surface_init(d_mu, nu, bond, crystal);

    // get surface ready for KMC Method
    KMC_init(crystal);


    //Run simulation
    KMC_run(crystal, step_num, rng, nu, bond);

    double tot = 0.;
    for (int i = 0; i < n ; ++i) {
        for (int j = 0; j < n; ++j) {
            tot+= crystal->cells[i][j].h;
        }
    }

//    total growth layers
    cout << tot/(n*n) << endl;
    FILE *f_layers = fopen("Layers", "w");
    fprintf(f_layers,"Total growth layers: %lf\n",tot/(n*n));
    fclose(f_layers);

    free(crystal);

    return 0;
}








