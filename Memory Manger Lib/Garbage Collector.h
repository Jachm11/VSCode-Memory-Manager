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
    static void GCInit();

    ///
    /// @brief Metodo que inicializa la clase como un singleton o retorna la instacia ya existente
    /// @author Jose
    ///
    static GarbageCollector* getInstance();

    ///
    /// @brief Metodo que se ejecuta cuando un nuevo VSPtr es creado
    /// @param La direccion de memoria de un VSPtr
    /// @author Jose
    ///
    template <class T>
    static void newPtr (VSPtr<T>*,void*,string);

    ///
    /// @brief Genera un ID para un nuevo VSPtr con base en IDref
    /// @author Jose
    ///
    static int generateID();

    ///
    /// @brief Metodo que se ejecuta cuando un VSPtr es eliminado
    /// @param La direccion de memoria de un VSPtr
    /// @author Jose
    ///
    template <class T>
    static void clear(VSPtr<T>*, void*);

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
    /// @brief Inicializa el servidor para la comunicacion con la extension
    /// @author Jose
    static void startServer();


    ///
    /// @brief Funcion que se encarga de tomar los datos registrados en el GC y darles formato para ser enviados a la extension
    /// @return Un string con todos los daros de las varibles guardadas
    /// @author Jose
    static string dataTosend();

    ///
    /// @brief Funcion que tomas los datos de los punteros registrados y los pasa a un string JSON
    /// @return JSON de los VSptr's
    /// @author Jose
    static string toJson();

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
    static void newPtrImp (VSPtr<T>*,void*,string);

    ///
    /// @brief Implemetacion de update
    /// @author Jose
    ///
    template <typename T>
    static void updateImp (T*,T*);

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

    static int searchInPtrs(void*);


};