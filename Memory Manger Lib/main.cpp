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

    int var = 34;
    int var2 = 1;

    VSPtr<int> myPtr0= VSPtr<int>::New();
    VSPtr<string> myPtr1= VSPtr<string>::New();
    VSPtr<int> myPtr2= VSPtr<int>::New();
    VSPtr<int> myPtr3= VSPtr<int>::New();
    VSPtr<int> myPtr4= VSPtr<int>::New();
    VSPtr<int> myPtr5= VSPtr<int>::New();
    VSPtr<int> myPtr6= VSPtr<int>::New();


    myPtr0.init();
    myPtr1.init();
    myPtr0 = 3;
    myPtr1 = "holas";


    sleep(1);
    //myPtr.hola();
    //myPtr.destroy();
    myPtr2.init();
    //myPtr3.init();
    //myPtr4.init();

    myPtr2 = var;
    myPtr3 = addressof(myPtr2);
    myPtr4 = addressof(myPtr2);

    sleep(1);

    myPtr5.init();
    myPtr5 = 54.43;

    sleep(1);

    myPtr6 = addressof(myPtr5);

    cout<< GarbageCollector :: toJson() <<endl;

    sleep(1000);
    

    return 0;
}
