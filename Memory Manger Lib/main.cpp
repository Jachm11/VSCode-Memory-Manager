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

    GarbageCollector :: GCInit();

    VSPtr<int> myPtr0= VSPtr<int>::New();
    VSPtr<double> myPtr1= VSPtr<double>::New();
    VSPtr<char> myPtr2= VSPtr<char>::New();
    VSPtr<string> myPtr3= VSPtr<string>::New();
    VSPtr<bool> myPtr4= VSPtr<bool>::New();
    VSPtr<float> myPtr5= VSPtr<float>::New();
    VSPtr<short> myPtr6= VSPtr<short>::New();
    VSPtr<unsigned> myPtr7= VSPtr<unsigned>::New();
    VSPtr<cosa> myPtr8= VSPtr<cosa>::New();

    VSPtr<int> myPtr9= VSPtr<int>::New();
    VSPtr<int> myPtr10= VSPtr<int>::New();
    VSPtr<bool> myPtr11= VSPtr<bool>::New();

    short shr = 123;
    unsigned usg = 12;
    cosa hola;


    myPtr0.init();
    myPtr1.init();

    myPtr0 = 3;
    myPtr1 = 85.65454345;

    sleep(10);

    myPtr2.init();
    myPtr3.init();
    myPtr4.init();

    myPtr2 = 'J';
    myPtr3 = "holas";
    myPtr4 = true;

    sleep(10);

    myPtr5.init();
    myPtr6.init();
    myPtr7.init();
    myPtr8.init();

    myPtr5 = 54.4;
    myPtr6 = shr;
    myPtr7 = usg;
    myPtr8 = hola;

    sleep(10);

    myPtr9 = addressof(myPtr0);

    sleep(10);

    myPtr10 = addressof(myPtr0);
    myPtr11 = addressof(myPtr4);


    sleep(30);

    
    return 0;
}
