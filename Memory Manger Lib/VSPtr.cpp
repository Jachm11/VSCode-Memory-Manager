#include "vsptr.h"
#include <iostream>

using namespace std;


template <class T>
VSPtr<T>::VSPtr()
{
    dato = (int *)malloc(sizeof(T));
}
template <class T>
void VSPtr<T>::New()
{

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
T VSPtr<T>::operator *()
{
    cout << "prueba *";
    return *dato;
}

template <class T>
void VSPtr<T>::freeMemory()
{
    free(dato);
}

template <class T>
void VSPtr<T>::hola()
{

    cout << "Numero" << *dato << endl;
    cout << "Espacio del puntero" << &dato << endl;
    cout << "Espacio del numero" << &*dato << endl;

}
