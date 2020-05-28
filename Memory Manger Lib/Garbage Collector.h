#include "linkedlist.cpp"
#include "VSPtr.h"

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
    /// @attention Cada vez que se crea un nuevo VSPtr (con NEW() y con "=")
    ///
    static void update (int ref);

    ///
    /// @brief Metodo que se ejecuta cuando un VSPtr es eliminado
    /// @param La direccion de memoria de un VSPtr
    /// @author Jose
    /// @attention Se usa cuando se llama al destructor del VSPtr
    ///
     static void clear(int ref);

    GarbageCollector(const GarbageCollector&) = delete;

private:

    
    LinkedList<int*> VSptrs;
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
    static void* inspect(void* arg);

    ///
    /// @brief Implemetacion de update
    /// @author Jose
    ///
    static void updateImp (int ref);

    ///
    /// @brief Genera un ID para un nuevo VSPtr con base en IDref
    /// @author Jose
    ///
    static int generateID();

    ///
    /// @brief Implemetacion de clear
    /// @author Jose
    ///
    static void clearImp(int ref);

    ///
    /// @brief Accede a la lista enlazada y busca los datos del VSPointr cuya dir de memoria sea igual a ref
    /// @param La direccion de memoria de un VSPtr
    /// @return Un array con los datos del VSPtr
    /// @author Jose
    ///
    static int* searchByRef(int ref);


};