#include <iostream>
#include "VSPtr.cpp"

using namespace std;


///
    /// @attention LINEA PARA COMPILAR EL CODIGO EL AL TERMINAL: g++ main.cpp -o main -pthread
    /// @attention LINEA PARA CORRER EL CODIGO EN LA TERMINAL: ./main
    ///
int main(int argc, char const *argv[])
{
    //LinkedList<int> hola;
    //LinkedList<int> hola2;
    //hola.insertFirst(10);
    //std::cout<< "hola" << std::endl;
    //std::cout<< hola2.getHead() << std::endl;
    //int var = hola.getHead()->getData();
    //print(var);
    //print(hola.searchByIndex(1)->getData());
    //print(hola.getSize());
    //cout << "Puntero1" << endl;


    //(GarbageCollector :: GCInit());

    VSPtr<int> myPtr= VSPtr<int>::New();
    myPtr.init();
    int var = 34;
    myPtr = 34;
    myPtr.hola();

    VSPtr<int> hola;
    myPtr = hola;

    //myPtr.destroy();


    return 0;
}
