#define VSPTR_H
#include <iostream>
using namespace std;

template <class T>
class VSPtr
{
private:
    VSPtr<T> *direccion;
    T *dato;
public:

    static VSPtr<T> New();
    VSPtr();
    void operator =(T data);
    void operator =(VSPtr<T> ptr2);
    VSPtr<T> operator *();
    T operator &();
    void setRef(VSPtr<T> *ref);
    void freeMemory();
    void hola();
};

#endif // VSPTR_H