#include "VSPtr.h"
#include <iostream>

using namespace std;




template <class T>
void VSPtr<T>::saveSize()
{
    dato = (T*)malloc(sizeof(T*));

}
template <class T>
VSPtr<T> VSPtr<T>::New()
{
    
    VSPtr<T> myPtr;
    VSPtr<T>* address;
    address = addressof(myPtr);
    // enviar a garbage collector
    cout << "HELP: " <<  address << endl;
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

template <class T>
VSPtr<T> VSPtr<T>::operator *()
{
    return *this;
    
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
    cout << "Espacio del numero" << dato << endl;
    cout << "Espacio del VSPtr" << this << endl;

}
