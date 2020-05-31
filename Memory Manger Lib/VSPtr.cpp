#include "VSPtr.h"
#include <iostream>
#include "Garbage Collector.cpp"

using namespace std;

template <class T>
VSPtr<T>::VSPtr(){
    dato = (T*)malloc(sizeof(T*));
}

template <class T>
VSPtr<T> VSPtr<T>::New()
{
    
    VSPtr<T> myPtr;
    //VSPtr<T>* address;
    //address = addressof(myPtr);
    // enviar a garbage collector
    //cout << "HELP: " <<  address << endl;
    return myPtr;
}

template <class T>
void VSPtr<T>::init()
{
    GarbageCollector::newPtr(this,&dato);
    cout << "ref de dato" << &dato <<endl;
}
template <class T>
void VSPtr<T>::operator =(T data)
{
    *dato = data;
}


template <class T>
void VSPtr<T>::operator =(VSPtr<T> ptr2)
{
    dato = &*ptr2.dato;
    GarbageCollector::newPtr(this,&dato);
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
void VSPtr<T>::destroy()
{
    GarbageCollector::clear(this, &dato);
    free(this);
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
