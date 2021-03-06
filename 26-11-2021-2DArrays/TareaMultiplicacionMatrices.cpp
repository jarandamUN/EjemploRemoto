#include <iostream>
#include <chrono>
#include <random>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>

void multiply(const std::vector<double> & m1, const std::vector<double> & m2, std::vector<double> & m3);

int main(int argc, char **argv) {
    // read parameters
    const int N = std::atoi(argv[1]);
    const int SEED = std::atoi(argv[2]);

    // data structs
    std::vector<double> A(N*N, 0.0), B(N*N, 0.0), C(N*N, 0.0);

    // fill matrices A and B, using random numbers betwwen 0 and 1
    std::mt19937 gen(SEED);
    std::uniform_real_distribution<> dist(0.,1.);
    // lambda function: a local function that captures [] something, receives something (), and return something {}
    // See: https://www.learncpp.com/cpp-tutorial/introduction-to-lambdas-anonymous-functions/
    std::generate(A.begin(), A.end(), [&gen, &dist](){ return dist(gen); }); // uses a lambda function
    std::generate(B.begin(), B.end(), [&gen, &dist](){ return dist(gen); }); // uses a lambda function

    // multiply the matrices A and B and save the result into C. Measure time
    auto start = std::chrono::high_resolution_clock::now();
    multiply(A, B, C);
    auto stop = std::chrono::high_resolution_clock::now();

    // use the matrix to avoid the compiler removing it
    std::cout << C[N/2] << std::endl;

    // print time
    auto elapsed = std::chrono::duration<double>(stop - start);
    std::cout << elapsed.count() << "\n";


    return 0;
}

// implementations
void multiply(const std::vector<double> & m1, const std::vector<double> & m2, std::vector<double> & m3)
{
    const int N = std::sqrt(m1.size()); // assumes square matrices
    double sum = 0.0;

    for(int ii = 0; ii < N ; ii++ ){                    // Varia los coeficientes principales para acceder 
        for(int jj = 0; jj < N ; jj++ ){                //     a cada una de las componentes de m3
        
            for(int k = 0; k < N ; k++ ){               // Cada valor m3[i][j] = m1[i][k]*m2[k][j] + m1[i][k+1]*m2[k+1][j] + ... + m1[i][N-1]*m2[N-1][j]
                sum += m1[ii*N + k]*m2[k*N + jj];       // Donde k es alguna variable 0<=k<N    (Perdonen si hay alg??n error en la digitaci??n)
            }                                           
        
            m3[ii*N + jj] = sum;                        // Almacena en m3[i][j] la sumatoria que comento en la linea #52 
            sum = 0.0;                                  // Resetea la sumatoria para no interferir con los dem??s valores de m3
        }
    }
}