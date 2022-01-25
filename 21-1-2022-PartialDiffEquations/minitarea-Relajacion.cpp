#include <iostream>
#include <vector>
#include <cmath>

// constants
const double DELTA = 0.05;
const double Lx = 1.479;
const double Ly = 1.4*Lx;
const int Nx = int(Lx/DELTA)+1;                   //Tamaño de la matriz, total de filas
const int Ny = int(Ly/DELTA)+1;                   //Tamaño de la matriz, total de columnas
                                                                                                           //Definicion de constantes adicionales
const int X1 = int(Lx/(3*DELTA));                 //Posicion en x de la primera placa
const int X2 = int(2*Lx/(3*DELTA));               //Posicion en x de la segunda placa
const int Y1 = int(Ly/(4*DELTA));                 //Posición en y donde empiezan ambas placas
const int Y2 = int(3*Ly/(4*DELTA));               //Dado que empieza en Ly/4 y tiene una longitud de Ly/2, Y2 = Ly/4 + Ly/2

const int STEPS = 200;

typedef std::vector<double> Matrix; // alias

void initial_conditions(Matrix & m);
void boundary_conditions(Matrix & m);
void evolve(Matrix & m);
void print(const Matrix & m);
void init_gnuplot(void);
void plot_gnuplot(const Matrix & m);

int main(void)
{
  Matrix data(Nx*Ny);
  initial_conditions(data);
  boundary_conditions(data);

  init_gnuplot();
  for (int istep = 0; istep < STEPS; ++istep) {
    evolve(data);
    plot_gnuplot(data);
  }

  return 0;
}
void initial_conditions(Matrix & m)
{
  for(int ii=0; ii<Nx; ++ii) {
    for(int jj=0; jj<Ny; ++jj) {
      m[ii*Ny + jj] = 1.0;
    }
  }
}
void boundary_conditions(Matrix & m)
{
  int ii = 0, jj = 0;

  ii = 0;
  for (jj = 0; jj < Ny; ++jj)
    m[ii*Ny + jj] = 100;

  ii = X1;                                                //Placa 1
  for (jj = Y1; jj < Y2; ++jj)
    m[ii*Ny + jj] = 75;
  
  ii = X2;                                                //Placa 2
  for (jj = Y1; jj < Y2; ++jj)
    m[ii*Ny + jj] = -75;

  ii = Nx-1;
  for (jj = 0; jj < Ny; ++jj)
    m[ii*Ny + jj] = 0;

  jj = 0;
  for (ii = 1; ii < Nx-1; ++ii)
    m[ii*Ny + jj] = 0;

  jj = Ny-1;
  for (ii = 1; ii < Nx-1; ++ii)
    m[ii*Ny + jj] = 0;
}

void evolve(Matrix & m)
{
  for(int ii=0; ii<Nx; ++ii) {
    for(int jj=0; jj<Ny; ++jj) {
      // check if boundary
      if(ii == 0) continue;
      if(ii == Nx-1) continue;
      if(jj == 0) continue;
      if(jj == Ny-1) continue;
      if(ii == X1) continue;                        //Sacar placas 1 y 2 de la relajacion
      if(ii == X2) continue;                        //
      // evolve non boundary
      m[ii*Ny+jj] = (m[(ii+1)*Ny + jj] +
                    m[(ii-1)*Ny + jj] +
                    m[ii*Ny + jj + 1] +
                    m[ii*Ny + jj - 1] )/4.0;
    }
  }
}

void print(const Matrix & m)
{
  for(int ii=0; ii<Nx; ++ii) {
    for(int jj=0; jj<Ny; ++jj) {
      std::cout << ii*DELTA << " " << jj*DELTA << " " <<  m[ii*Ny + jj] << "\n";
    }
    std::cout << "\n";
  }  
}

void init_gnuplot(void)
{
  std::cout << "set contour " << std::endl;
  std::cout << "set terminal gif animate " << std::endl;
  std::cout << "set out 'anim.gif' " << std::endl;
}

void plot_gnuplot(const Matrix & m)
{
  std::cout << "splot '-' w pm3d " << std::endl;
  print(m);
  std::cout << "e" << std::endl;
}