#ifndef VSPTR_H
#define VSPTR_H

template <class T>
class VSPtr
{
private:
public:
    VSPtr();
    void New();
    T *dato;
    void operator =(T data);
    void operator =(VSPtr<T> ptr2);
    T operator *();
    T operator &();
    void freeMemory();
    void hola();
};

#endif // VSPTR_H
