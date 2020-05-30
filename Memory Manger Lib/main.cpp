#include "Garbage Collector.cpp"
#include <iostream>

#include "VSPtr.cpp"

using namespace std;

void print(int x){

    //std::cout<< x << std::endl;

}

void print(char* x){

    //std::cout<< x << std::endl;

}

int main(int argc, char const *argv[])
{
    //LinkedList<int> hola;
    //LinkedList<int> hola2;

    //(GarbageCollector :: GCInit());

    //hola.insertFirst(10);

    //std::cout<< "hola" << std::endl;
    //std::cout<< hola2.getHead() << std::endl;




    //int var = hola.getHead()->getData();

    //print(var);

    //print(hola.searchByIndex(1)->getData());

    //print(hola.getSize());

    cout << "Puntero1" << endl;
    VSPtr<int> myPtr;
    myPtr = 34;
    myPtr.hola();

    cout << "Puntero 2" << endl;

    VSPtr<int> myPtr2;
    myPtr2 = myPtr;
    //myPtr2.freeMemory();
    myPtr2.hola();

    int val = &myPtr;
    cout << val << endl;

    return 0;
}
