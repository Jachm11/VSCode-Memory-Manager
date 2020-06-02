#pragma once
#include "VSPtr.cpp"

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

