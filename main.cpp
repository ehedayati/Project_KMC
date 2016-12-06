#include "main.h"




int main() {
    std::mt19937 rng;
    rng.seed(seeder());
    //initialization conditions
    int n = 5;
    float d_mu = 1;
    float nu = 1;
    float temp = 1;
    int step_num = 5;

    //initializing surface
    Surface *crystal = new Surface();
    crystal->n = n;
    surface_init(d_mu, nu, temp, crystal);

    // get surface ready for KMC Method
    KMC_init(crystal);

    //Run simulation
    KMC_run(crystal, step_num, rng, nu, temp);


    cout << endl;

    for (int i = 0; i < n ; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d\t",crystal->cells[i][j].h);
        }
        cout << endl;
    }
    free(crystal);
//    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");

    return 0;
}







