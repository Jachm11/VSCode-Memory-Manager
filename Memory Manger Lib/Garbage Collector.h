#pragma once
#include "linkedlist.cpp"
#include "GCStructs.h"

///
/// @brief Clase Singleton que simula un Garbage collector
/// @author Jose
///
class GarbageCollector{

public:

    ///
    /// @brief Metodo que inicializa el thread de la clase
    /// @author Jose
    /// @attention Se usa al iniciar el programa en el main (como tkinter)
    static void GCInit();

    ///
    /// @brief Metodo que inicializa la clase como un singleton o retorna la instacia ya existente
    /// @author Jose
    /// @attention La insignia de un singleton. Se usa antes de cada funcion. i.e GarbageCollector.getInstance()->funcion() (creo jeje)
    ///
    static GarbageCollector* getInstance();

    ///
    /// @brief Metodo que se ejecuta cuando un nuevo VSPtr es creado
    /// @param La direccion de memoria de un VSPtr
    /// @author Jose
    /// @attention Cada vez que se crea un nuevo VSPtr
    ///
    template <class T>
    static void newPtr (VSPtr<T>* VSDir,void* TDir);

    ///
    /// @brief Genera un ID para un nuevo VSPtr con base en IDref
    /// @author Jose
    ///
    static int generateID();

    ///
    /// @brief Metodo que se ejecuta se cambia la referencia de VSPtr
    /// @param La direccion de memoria de un VSPtr
    /// @author Jose
    /// @attention Cada vez que se cambia la referencia de VSPtr
    ///
    template <typename T>
    static void update (T* oldDir,T* newDir);

    ///
    /// @brief Metodo que se ejecuta cuando un VSPtr es eliminado
    /// @param La direccion de memoria de un VSPtr
    /// @author Jose
    /// @attention Se usa cuando se llama al destructor del VSPtr
    ///
    template <class T>
    static void clear(VSPtr<T>* VSDir,void* TDir);

    GarbageCollector(const GarbageCollector&) = delete;

private:

    
    LinkedList<VSPointers> VSptrs;
    LinkedList<VSData> Data;
    int IDref;
    bool init = false;

    GarbageCollector();

    ///
    /// @brief Implemetacion de GCInit
    /// @author Jose
    ///
    static void GCInitImp();

    ///
    /// @brief Metodo que se ejecuta en el thread, busca aquellos VSPtr cuya referencia es 0
    /// @author Jose
    ///
    static void inspect();

    ///
    /// @brief Implemetacion de newPtr
    /// @author Jose
    ///
    template <class T>
    static void newPtrImp (VSPtr<T>* VSDir,void* TDir);

    ///
    /// @brief Implemetacion de update
    /// @author Jose
    ///
    template <typename T>
    static void updateImp (T* oldDir,T* newDir);

    ///
    /// @brief Implemetacion de generateID
    /// @author Jose
    ///
    static int generateIDImp();

    ///
    /// @brief Implemetacion de clear
    /// @author Jose
    ///
    template <class T>
    static void clearImp(VSPtr<T>* VSDir,void* TDir);

    ///
    /// @brief Accede a la lista enlazada y busca los datos del VSPointr cuya dir de memoria sea igual a ref
    /// @param La direccion de memoria de un VSPtr
    /// @return Un array con los datos del VSPtr
    /// @author Jose
    ///
    static VSData* searchInData(void*);

    static VSPointers* searchInPtrs(void*);


};