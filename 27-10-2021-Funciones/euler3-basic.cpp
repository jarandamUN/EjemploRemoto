#include <iostream>
//Numero primo divisor más grande de N

bool isprime(long long n ); //declaration
long long int largestPrimeDivisor(long long int n);

int main(void){
    
    const long long int N = 600851475147;
    std::cout << largestPrimeDivisor(N) << std::endl;
    
    return 0;
}

bool isprime(long long n){
    bool isprime = true;
    for (long long int jj = 2; jj < n; jj++){
                if(n % jj == 0 ){
                    isprime = false;
                    break;
                }
            }
    return isprime;
}

long long int largestPrimeDivisor(long long int n){
    long long int maxPrimeDivisor = 1;
    for(long long int ii = 2; ii < n; ii++ ){
        if(n % ii == 0){
            maxPrimeDivisor = n/ii;
            if(isprime(maxPrimeDivisor) == true){
                
                break;
            }
            
        }
    }

    return maxPrimeDivisor;
}