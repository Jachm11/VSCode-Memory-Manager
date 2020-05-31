#define VSPTR_H
#include <iostream>
using namespace std;

template <class T>
class VSPtr
{
private:
    VSPtr<T> *direccion;
    
public:
    T *dato;
    static VSPtr<T> New();
    void operator =(T data);
    void operator =(VSPtr<T> ptr2);
    VSPtr<T> operator *();
    T operator &();
    void setRef(VSPtr<T> *ref);
    void saveSize();
    void freeMemory();
    void hola();
};
