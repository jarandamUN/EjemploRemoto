#include <iostream>

int main(void){

    int m = 100;
    int suma = 0;
    for(int i = 1; i < m; i++){

        if((i%3 == 0) || (i%5 == 0)){
            
            suma += i;
            std::cout << i << std::endl;

        }

    }

    std::cout << suma << std::endl;
    return 0;
}