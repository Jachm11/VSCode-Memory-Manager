#pragma once
#include "VSPtr.h"

struct VSPointers
{
    VSPtr<void*>* dir;
    int ID;

};


struct VSData
{
    void* dir;
    int refs;
};

