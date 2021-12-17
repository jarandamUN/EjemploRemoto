#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>
#include <map>
#include <random>
#include <fstream>

int main(int argc, char **argv){

    const int N = std::atoi(argv[1]);

    std::vector<int> V(N, 0);
    std::iota(V.begin(), V.end(), 10);
    
    auto print = [] (const int &n){std::cout << " " << n; };
    std::cout << "  Vector: ";
    std::for_each(V.begin(), V.end(), print);
    std::cout << "\n";

    int count_Mayor25 = std::count_if(V.begin(), V.end(), [](int i){return i > 25;});
    std::cout << "  Mayores a 25 en V : " << count_Mayor25 << std::endl;

    int count_Div3Y5 = std::count_if(V.begin(), V.end(), [](int i){return i % 3 == 0 && i % 5 == 0;});
    std::cout << "  Divisibles entre 3 y 5 : " << count_Div3Y5 << std::endl;

    std::cout << "  Alguno divisible entre 7 y 13 (true = 1): " << std::any_of(V.cbegin(), V.cend(), [](int i){return i % 7 == 0 && i % 13 == 0;}) << std::endl;
    
    std::sort(V.begin(), V.end(), [](int a, int b){return a > b;});
    std::cout << "  Primeros 10 ordenados: ";
    std::for_each_n(V.begin(), 10, print);                                     //usar: g++ -std=c++17 minitarea-STL.cpp    al compilar
    std::cout << "\n";

    auto start = std::chrono::high_resolution_clock::now();
    double promedio = std::accumulate(V.begin(), V.end(), 0)/N;
    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration<double>(stop - start);
    std::cout << "  Tiempo : " << elapsed.count() << "\n";

    std::mt19937 gen(5);
    std::normal_distribution <> dis(0,1);                                      //siguiendo la distribución normal estándar 
    std::map <int, int> histo;
    for(int ii = 0; ii < 10000; ii++){
        ++histo[std::round(dis(gen))];
    }
    
    std::ofstream fout("histo.txt");
    fout.precision(15); fout.setf(std::ios::scientific);

    for (auto p : histo) {                    
        fout << p.first << "\t" << p.second << "\n";
    }
    fout.close();

    return 0;
}