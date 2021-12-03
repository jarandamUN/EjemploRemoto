#include <iostream>

class Vector3D
{   
    private:
        int Rx, Ry, Rz;
    public:
        Vector3D(int x = 0, int y = 0, int z = 0){
            Rx = x;
            Ry = y;
            Rz = z;
        }

        ~Vector3D(){
            Rx, Ry, Rz = 0;
        }

        Vector3D operator + (Vector3D const &obj){
            Vector3D res;
            res.Rx = Rx + obj.Rx;
            res.Ry = Ry + obj.Ry;
            res.Rz = Rz + obj.Rz;
            return res;
        }
        
        int operator * (Vector3D const &obj){
            int dot = Rx * obj.Rx + Ry * obj.Ry + Rz * obj.Rz;

            return dot;
        }

        void print(){
            std::cout << "(" << Rx << ", " << Ry << ", " << Rz << ")"<< std::endl;
        }

};


int main(){

    Vector3D v1(1, 2, 3), v2(4, 5, 6);
    Vector3D v3 = v1 + v2;
    v3.print();
    
    int productoPunto =  v1 * v2;
    std::cout << "Producto Punto: " <<  productoPunto  << std::endl;

    return 0;
}