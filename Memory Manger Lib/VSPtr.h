#pragma once
#include <iostream>
using namespace std;

template <class T>
class VSPtr
{
private:
    T *dato;
    int IDref;
    
    
public:

    ///
    /// @brief Constructor de la clase
    /// @author Natalia
    ///
    VSPtr();
    ///
    /// @brief Destructor de la clase, le avisa al Garbage Collector que se eliminó el puntero y vacía el espacio de referencia en el que estaba
    /// @author Natalia
    ///
    ~VSPtr<T>();

    ///
    /// @brief 
    /// @author Natalia
    ///
    static VSPtr<T> New();
    ///
    /// @brief Inicializa el VSPtr y envía su referencia y la del puntero dato al Garbage Collector
    /// @author Natalia
    ///
    void init();
    ///
    /// @brief Le asigna data a la dirección de memoria reservada a la que apunta dato
    /// @param Un dato tipo T
    /// @author Natalia
    ///
    void operator =(T data);
    ///
    /// @brief Pone a ambos punteros a apuntar a la misma dirección de memoria
    /// @param Un VSPtr
    /// @author Natalia
    ///
    void operator =(VSPtr<T> ptr2);
    ///
    /// @brief Obtener el valor al que apunta el puntero
    /// @return El valor al que apunta dato
    /// @author Natalia
    ///
    T operator &();
    ///
    /// @brief Obtener el mismo objeto
    /// @return El mismo VSPtr
    /// @author Natalia
    ///
    VSPtr<T> operator *();
    
    ///
    /// @brief Obtener el ID del VSPtr
    /// @return IDRef
    /// @author Natalia
    ///
    int getIDref();
    
    void hola();
};
