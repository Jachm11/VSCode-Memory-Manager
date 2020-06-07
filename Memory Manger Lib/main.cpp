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


    (GarbageCollector :: GCInit());

    //int var = 34;
    //int var2 = 1;

    VSPtr<int> myPtr= VSPtr<int>::New();
    VSPtr<string> myPtr2= VSPtr<string>::New();
    //VSPtr<int> myPtr3= VSPtr<int>::New();
    //VSPtr<int> myPtr4= VSPtr<int>::New();

    myPtr.init();
    myPtr2.init();
    myPtr =3;
    myPtr2 = "holas";

    sleep(30);
    //myPtr.hola();
    //myPtr.destroy();
    //myPtr4.init();

    /*myPtr = var;
    myPtr.hola();

    myPtr4 = var;
    myPtr4.hola();

    myPtr2 = myPtr;
    myPtr2.hola();
    myPtr3 = myPtr2;

    myPtr.destroy();

    sleep(5);

    myPtr2.destroy();

    sleep(5);

    myPtr3.destroy();*/
    


    return 0;
}
