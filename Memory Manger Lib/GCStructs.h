#pragma once
#include "VSPtr.h"

struct VSPointers
{
    VSPtr<void*>* dir;
    void* dato;
    int ID;
    string tipo;

};


struct VSData
{
    void* dir;
    int refs;
    string tipo;
};

