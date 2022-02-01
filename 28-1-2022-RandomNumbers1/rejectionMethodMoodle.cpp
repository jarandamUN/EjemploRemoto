#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include <vector>

double pdf(double x);

int main(int argc, char **argv)
{
    const int SEED = std::atoi(argv[1]);;                        //Definicion de constantes pedidad por consola
    const int SAMPLES = std::atoi(argv[2]);
    const double XMIN = std::atoi(argv[3]);
    const double XMAX = std::atoi(argv[4]);
    const int NBINS = std::atoi(argv[5]);
  
    const double DX = (XMAX-XMIN)/NBINS;

    std::vector<double> histo(NBINS, 0.0);
    std::mt19937 gen(SEED);

    std::uniform_real_distribution<double> valX(-1, 1);           //Dominio de la pdf dado en la tarea
    std::uniform_real_distribution<double> valY(0, 3.0/4.0);      //Rango de la pdf, de 0 al máximo de pdf

    std::ofstream fout("datos.txt");                              //Impresión de los datos aleatorios generados
    for (int ii = 0; ii < SAMPLES;) {
        double xs = valX(gen);
        double ys = valY(gen);
        if(ys < pdf(xs)){                                         //Rejection Method
            fout << xs << "\n";
            int bin = int((xs - XMIN)/DX);
            if (0 <= bin && bin < NBINS) {
                histo[bin]++;
                ++ii;
            }
        }
    }
    fout.close();

    fout.open("density.txt");                                     //Impresión de la pdf
    for (int ii = 0; ii < NBINS; ii++) {
        fout << XMIN + ii*DX << "\t" << histo[ii]/(DX*SAMPLES) << "\n";
    }
    fout.close();

    return 0;
}

double pdf(double x){                                              //Probability density function
    return 3.0*(1-x*x)/4.0;
}