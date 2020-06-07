#include "VSPtr.h"
#include "Garbage Collector.cpp"
#include <iostream>

using namespace std;

template <class T>
VSPtr<T>::VSPtr(){
    dato = (T*)malloc(sizeof(T*));
}
template <class T>
VSPtr<T>::~VSPtr<T>()
{
    cout << "Se eliminó el VSPtr " <<  IDref << endl;
    GarbageCollector::clear(this, dato);

}
template <class T>
VSPtr<T> VSPtr<T>::New()
{
    VSPtr<T> myPtr; 
    return myPtr;
}

template <class T>
void VSPtr<T>::init()
{
    GarbageCollector::newPtr((VSPtr<void*>*)this,dato);
    IDref = GarbageCollector:: generateID();
    //cout << "ref de dato: " << dato <<endl;
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
    GarbageCollector::newPtr((VSPtr<void*>*)this,dato);
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
int VSPtr<T>::getIDref()
{
    return IDref;
}

template <class T>
void VSPtr<T>::hola()
{

    cout << "Número: " << *dato << endl;
    cout << "Espacio del puntero: " << &dato << endl;
    cout << "Espacio del numero: " << dato << endl;
    cout << "Espacio del VSPtr: " << this << endl;
}
