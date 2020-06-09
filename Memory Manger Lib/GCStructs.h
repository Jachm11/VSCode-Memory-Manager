#pragma once
#include "VSPtr.h"

///
///@brief Estructura para almacenar los datos de un VSPtr especifico
///@author Jose
///
struct VSPointers
{
    VSPtr<void*>* dir;
    void* dato;
    int ID;
    string tipo;

};

///
///@brief Estructura para almacenar los datos de una variable en el heap
///@author Jose
///
struct VSData
{
    void* dir;
    int refs;
    string tipo;
};

