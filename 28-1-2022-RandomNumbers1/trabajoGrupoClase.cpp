#include <iostream>
#include <random>
#include <map>
#include <cmath>
#include <vector>
 
int main()
{
    const int seed = 300;
    const int tamaño = 1000;
    const int grados = 4;

    std::mt19937 gen{seed};
    std::chi_squared_distribution<double> chi_dist(grados);

    //Guardar los datos
    for(int ii = 0; ii < tamaño; ii++){

    }

    //Imprimirlo
    std::map<int, int> hist;
    for (int n = 0; n < tamaño; ++n) {
        ++hist[std::round(chi_dist(gen))];
    }

    return 0;
}