#include <iostream>
int main(void){
    
    long long int N = 108; //600851475147
    long long  int maxDivisor = 1;

    for(long long int i = 1; i < N; i++ ){
        if(N % i == 0){
            maxDivisor = i;
            std::cout << "Un divisor: " << i << std::endl;
        }
    }

    std::cout << "El mayor divisor de " << N << " es: " << maxDivisor << std::endl;


    
    return 0;
}