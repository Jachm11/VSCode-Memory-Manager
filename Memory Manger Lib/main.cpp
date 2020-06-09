#include <iostream>
#include "VSPtr.cpp"


using namespace std;

struct cosa
{
    /* data */
};



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
    VSPtr<int> myPtr1= VSPtr<int>::New();
    VSPtr<int> myPtr2= VSPtr<int>::New();
    //VSPtr<string> myPtr3= VSPtr<string>::New();
    //VSPtr<bool> myPtr4= VSPtr<bool>::New();
    //VSPtr<float> myPtr5= VSPtr<float>::New();
    //VSPtr<short> myPtr6= VSPtr<short>::New();
    VSPtr<unsigned> myPtr7= VSPtr<unsigned>::New();
    VSPtr<cosa> myPtr8= VSPtr<cosa>::New();


    myPtr0.init();
    //myPtr1.init();
    //myPtr2.init();
    //myPtr3.init();
    //myPtr4.init();
    //myPtr5.init();
    //myPtr6.init();
    myPtr7.init();
    myPtr8.init();

    short shr = 123;
    unsigned usg = 12;
    cosa hola;

    myPtr0 = 3;
    //myPtr1 = 85.65454345;
    //myPtr2 = 'J';
    //myPtr3 = "holas";
    //myPtr4 = true;
    //myPtr5 = 54.4;
    //myPtr6 = shr;
    //myPtr7 = usg;
    myPtr8 = hola;

    myPtr1 = addressof(myPtr0);
    myPtr2 = addressof(myPtr0);


    sleep(1);


    sleep(1);



    sleep(1);


    cout<< GarbageCollector :: toJson() <<endl;

    sleep(1000);
    

    return 0;
}
