#include <iostream>
#include <cmath>
#include <cstdlib>

double f(double x);
template <class fptr>
double bisection(double xl, double xu, fptr fun, double eps);
template <class fptr>
double bisectionRecursiva(double xl, double xu, fptr fun, double eps);


int main(int argc, char **argv)
{
    std::cout.precision(16); std::cout.setf(std::ios::scientific);
  
    const double XL = std::atof(argv[1]);
    const double XU = std::atof(argv[2]);
    const double EPS = std::atof(argv[3]);


    std::cout << EPS << "\t"
            << bisection(XL, XU, f, EPS) << "\t"
            << bisectionRecursiva(XL, XU, f, EPS) << std::endl;
  
    return 0;
}

double f(double x)
{
    return 9.81*(68.1)*(1 - std::exp(-x*10/68.1))/x - 40;
}

template <class fptr>
double bisection(double xl, double xu, fptr fun, double eps)
{
    double xr = 0;
    for( ;  ; ) { // while(true)
        xr = (xl + xu)/2; // bisection
        // encontre la raiz?
        if (std::fabs(fun(xr)) <= eps) break;
      // actualizar los limites
      if (fun(xr)*fun(xl) < 0) {
        xu = xr;
        } else {
          xl = xr;
        }
     }
     return xr;
}

template <class fptr>
double bisectionRecursiva(double xl, double xu, fptr fun, double eps){

    double xr = (xl + xu)/2;
    if (std::fabs(fun(xr)) > eps){
        if (fun(xr)*fun(xl) < 0) {
            xu = xr;
        } else {
            xl = xr;
        }

        return bisectionRecursiva(xl, xu, fun, eps);
    }else{
        return xr;
    }
}