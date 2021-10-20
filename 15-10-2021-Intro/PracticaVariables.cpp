#include <iostream>

float Float1;
bool Bool = false;
double Double;
float Float2 = 1.0e40; //Probando con 1.0e10, 1.0e20, etc, vemos que esa es la forma de escribir en c++ la notación cientifica, es asi que al poner 1.0e4 nos apareceria 10000, y al anotar 1.0e40 tendriamos 10000000000000000000000000000000000000000, numero que el programa ya determina como demasiado grande y nos pone la definicion inf ("infinito").


int main(){
    
    std::cout << "Valor Float1: " << Float1 << "\n";
    std::cout << "Valor Bool: " << Bool << "\n";
    std::cout << "Double. Dirección memoria: " << &Double << " ,Bytes que ocupa: " << sizeof(Double) << "\n";
    std::cout << "Valor Float2: " << Float2 << "\n";

}

