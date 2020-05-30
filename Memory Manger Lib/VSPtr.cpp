#include "vsptr.h"
#include <iostream>

using namespace std;


template <class T>
VSPtr<T>::VSPtr()
{
    dato = (T*)malloc(sizeof(T*));
}
template <class T>
VSPtr<T> VSPtr<T>::New()
{
    VSPtr<T> *address;
    VSPtr<T> myPtr;
    address =addressof(myPtr);
    myPtr.setRef(address);
    cout << "HEELP: " << addressof(myPtr)  << endl;
    return myPtr;
}
template <class T>
void VSPtr<T>::operator =(T data)
{
    *dato = data;
}


template <class T>
void VSPtr<T>::operator =(VSPtr<T> ptr2)
{
    dato = ptr2.dato;
}

template <class T>
T VSPtr<T>::operator &()
{
    return *dato;
}

// Necesito retornar un vspointer pero para eso necesito la direccion donde esta guardado
template <class T>
 VSPtr<T> VSPtr<T>::operator *()
{
    cout << "prueba *";
    return *direccion;
}

template <class T>
void VSPtr<T>::freeMemory()
{
    free(dato);
}

template <class T>
void VSPtr<T>::setRef(VSPtr<T> *ref)
{
    direccion = ref;
}

template <class T>
void VSPtr<T>::hola()
{

    cout << "Numero" << *dato << endl;
    cout << "Espacio del puntero" << &dato << endl;
    cout << "Espacio del numero" << &*dato << endl;
    cout << "Espacio del VSPtr" << direccion << endl;

}
