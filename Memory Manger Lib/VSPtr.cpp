#include "VSPtr.h"
#include "Garbage Collector.cpp"
#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <string>
#include <memory>

using namespace std;



template <class T>
VSPtr<T>::VSPtr(){
    dato = (T*)malloc(sizeof(T*));

    std::unordered_map<std::type_index, std::string> type_names;
    type_names[std::type_index(typeid(int))] = "int";
    type_names[std::type_index(typeid(double))] = "double";
    type_names[std::type_index(typeid(char))] = "char";
    type_names[std::type_index(typeid(string))] = "string";
    type_names[std::type_index(typeid(bool))] = "bool";
    type_names[std::type_index(typeid(float))] = "float";
    type_names[std::type_index(typeid(short))] = "short";
    type_names[std::type_index(typeid(unsigned))] = "unsigned";
    string tipos[] = {"int","double","char","string","bool","float","short","unsigned"};

    tipo = type_names[std::type_index(typeid(T))];


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
    IDref = GarbageCollector:: generateID();
    GarbageCollector::newPtr((VSPtr<void*>*)this,dato,tipo);

}
template <class T>
void VSPtr<T>::operator =(T data)
{   

    *dato = data;

}


template <class T>
void VSPtr<T>::operator =(VSPtr<T>* ptr2)
{

    dato = ptr2->dato;
    IDref = ptr2->IDref;
    GarbageCollector::newPtr((VSPtr<void*>*)this,dato,tipo);
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
