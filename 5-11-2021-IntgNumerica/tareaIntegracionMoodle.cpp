#include <iostream>
#include <cmath>

using fptr = double(double);

double trapezoid(const double a, const double b, const int n, fptr func); //declaración
double simpson(const double a, const double b, const int n, fptr func);
double function(double x);
double exactaIntegral(double a, double b);


int main(void)
{
    const double Masa = 1.25;
    const int N1 = 10;
    const int N2 = 1000;
    const int a = 0;
    const int b = 4;

    double exactVelocidad = std::sqrt(2*exactaIntegral(a,b)/Masa);
    //std::cout << exactaIntegral(a, b) << "\n";                                 Comprobando valores especificos 
    //std::cout << exactVelocidad << "\n";
    //std::cout << std::sqrt(2*trapezoid(a, b, N2, function)/Masa) << "\n";
    //std::cout << std::sqrt(2*simpson(a, b, N2, function)/Masa) << "\n";


    std::cout << "N1: " << N1 << "\t" //estructura: 1 - sqrt(2*Integral/m)/VelocidadExacta 
                  << "Trapecio: " << std::fabs(1 - std::sqrt(2*trapezoid(a, b, N1, function)/Masa)/exactVelocidad) << "\t"  
                  << "Simpson: " << std::fabs(1 - std::sqrt(2*simpson(a, b, N1, function)/Masa)/exactVelocidad) << "\n";
    std::cout << "N2: " << N2 << "\t"
                  << "Trapecio: " <<  std::fabs(1 - std::sqrt(2*trapezoid(a, b, N2, function)/Masa)/exactVelocidad) << "\t"
                  <<  "Simpson: " << std::fabs(1 - std::sqrt(2*simpson(a, b, N2, function)/Masa)/exactVelocidad) << "\n";

    

    return 0;
}

double exactaIntegral(double a, double b){                                      //implementación

    //2*(-x*std::cos(x) + std::sin(x)) -> antiderivada

    return 2*(-b*std::cos(b) + std::sin(b)) -2*(-a*std::cos(a) + std::sin(a));
}

double function(double x){
   
    return 2*x*std::sin(x);
}

double trapezoid(const double a, const double b, const int n, fptr func){

    const double h = (b-a)/n;
    double sum = 0.5*(func(a) + func(b));
    for(int ii = 1; ii < n-1; ++ii) { 
        double x = a + ii*h;
        sum += func(x);
    }
    return h*sum;
}

double simpson(const double a, const double b, const int n, fptr func){

    double sum = 0, result = func(a) + func(b);
    double x;
    const double h = (b-a)/n;
   
    sum = 0;
    for(int ii = 1; ii <= n/2 - 1; ++ii ) {
        x = a + 2*ii*h;
        sum += func(x);
    }
    
    result += 2*sum;
    sum = 0;
    for(int ii = 1; ii <= n/2; ++ii ) {
        x = a + (2*ii-1)*h;
        sum += func(x);
    }
    result += 4*sum;  

    return result*h/3;

}