#include <iostream>
#include <cmath>
#include <vector>

typedef std::vector<long int> Matriz; 

double random_generator (long int x, long int a, long int c, long int m);
void print (Matriz &trip);


int main(){
  const long int X0 = 1;
  const long int A = 1664525;
  const long int C = 1013904223;
  const long int M = 4294967296;

  Matriz Tripleta(1000*3); 
  
Tripleta[0] = random_generator(X0, A, C, M);

  for (int ii = 1; ii < 3000; ++ii){
    Tripleta[ii] = random_generator(Tripleta[ii-1], A, C, M);
  }
    
  print(Tripleta);

    return 0;
}

double random_generator (long int &x, long int a, long int c, long int m){
  return (1.0)*((a*x + c)%m)/(m-1);
}

void print (Matriz &trip){
  for (int ii = 0; ii < 1000; ++ii){
    for (int jj = 0; jj < 3; ++jj){
      std::cout << trip[ii*3 + jj] <<' ';
    }
    std::cout << '\n';
  }
}
