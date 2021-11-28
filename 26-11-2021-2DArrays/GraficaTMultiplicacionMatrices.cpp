#include <iostream>
#include <chrono>
#include <random>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <fstream>

void multiply(const std::vector<double> & m1, const std::vector<double> & m2, std::vector<double> & m3);

int main(int argc, char **argv) {

  std::ofstream fout("histo.txt");
  for (int ibin = 4; ibin <= 512; ibin*= 2) {
    std::cout << "Ibin: " << ibin << std::endl;
    //int ibin = 64;
    std::vector<double> D(ibin*ibin, 0.0), E(ibin*ibin, 0.0), F(ibin*ibin, 0.0);
    std::mt19937 gen(10);
    std::uniform_real_distribution<> dist(0.,1.);
    std::generate(D.begin(), D.end(), [&gen, &dist](){ return dist(gen); }); // uses a lambda function
    std::generate(E.begin(), E.end(), [&gen, &dist](){ return dist(gen); });
  
    auto start = std::chrono::high_resolution_clock::now();
    multiply(D, E, F);
    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << F[ibin/2] << std::endl;

    auto elapsed = std::chrono::duration<double>(stop - start);

    std::cout << elapsed.count() << "\n";

    fout << ibin << "\t" << elapsed.count() << "\n";
  }
  fout.close();
  
  return 0;
}


void multiply(const std::vector<double> & m1, const std::vector<double> & m2, std::vector<double> & m3)
{
    const int N = std::sqrt(m1.size()); // assumes square matrices
    double sum = 0.0;

    for(int ii = 0; ii < N ; ii++ ){                    // Varia los coeficientes principales para acceder 
        for(int jj = 0; jj < N ; jj++ ){                //     a cada una de las componentes de m3
        
            for(int k = 0; k < N ; k++ ){               // Cada valor m3[i][j] = m1[i][k]*m2[k][j] + m1[i][k+1]*m2[k+1][j] + ... + m1[i][N-1]*m2[N-1][j]
                sum += m1[ii*N + k]*m2[k*N + jj];       // Donde k es alguna variable 0<=k<N    (Perdonen si hay algún error en la digitación)
            }                                           
        
            m3[ii*N + jj] = sum;                        // Almacena en m3[i][j] la sumatoria que comento en la linea #52 
            sum = 0.0;                                  // Resetea la sumatoria para no interferir con los demás valores de m3
        }
    }
}


