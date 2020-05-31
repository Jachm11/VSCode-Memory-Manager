#define VSPTR_H
#include <iostream>
using namespace std;

template <class T>
class VSPtr
{
private:

    
    
public:
    T *dato;
    VSPtr();
    static VSPtr<T> New();
    void init();
    void operator =(T data);
    void operator =(VSPtr<T> ptr2);
    VSPtr<T> operator *();
    T operator &();
    void destroy();
    void hola();
};
