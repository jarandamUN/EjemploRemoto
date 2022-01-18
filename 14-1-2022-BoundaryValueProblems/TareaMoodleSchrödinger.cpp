#include <iostream>
#include <cmath>
#include <cstdlib>
#include <boost/numeric/odeint.hpp>

const double pi = 4.0 * std::atan(1.0);
const double X0 = 0;
const double XF = pi/2;
const double DX = 0.01;

typedef std::vector<double> state_t;

void print(const state_t & y, double time);
template <class fptr>
double newton(double x0, fptr fun, double eps, int & niter);

int main(int argc, char **argv)
{
  
  const double E0 = std::atof(argv[1]);                           
  const double phi0 = std::atof(argv[2]);
  const double phidot0 = std::atof(argv[3]);
  const int N = 2;
  

  state_t y(N); // (T, z)

  // functor : A class or struct with overloaded ()
  // behaves as a function (but richer, includes a parameter in this case)
  // to declare use:
  // Fderiv func; func.E = value;
  struct Fderiv {
    double E_ = 0; //internal parameter
    void operator()(const state_t & y, state_t & dydt, double t) { //external interface, is a function
    // vector is : y = (y0, y1) = (phi, z), z = dphi/dx
    dydt[0] = y[1];
    dydt[1] = -E_*y[0];
    }
  };

  // create lambda function: receives one arg (Energy) and return the final T value minus the expected one.
  auto faux = [&y, phi0, phidot0](double E){
    y[0] = phi0; y[1] = phidot0;
    Fderiv j; j.E_ = E; // declare functor and assing internal var E  to lambda argument
    boost::numeric::odeint::integrate(j, y, X0, XF, DX);
    return y[0] - 0;
  };

  // perform a Newton-Raphson procedure to find the root
  // compute numerically the derivative
  int nsteps = 0;
  double z0  = newton(E0, faux, 0.000001, nsteps);                //Calculo de E
  y[0]=phi0; y[1]=phidot0;
  Fderiv k; k.E_ = z0;
  boost::numeric::odeint::integrate(k,y,X0,XF,DX,print);          //Función de Onda dado el E ya encontrado
  // print final data
  std::cerr << z0 << std::endl;                                   //E
  
  return 0;

}

template <class fptr>
double newton(double x0, fptr fun, double eps, int & niter)
{
  double h = 0.00001;
  double xr = x0;
  int iter = 1;
  while(std::fabs(fun(xr)) > eps) {
    double fderiv =  (fun(xr+h/2) - fun(xr-h/2))/h;
    xr = xr - fun(xr)/fderiv;
    iter++;
  }
  niter = iter;
  return xr;
}

void print(const state_t & y, double time)
{
  //std::cout << time << "\t" <<y[0] << "\t" << std::endl;
}
