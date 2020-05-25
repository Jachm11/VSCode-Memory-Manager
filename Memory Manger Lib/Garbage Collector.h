#include "linkedlist.cpp"
#include "VSPtr.cpp"

///
/// @brief Clase Singleton que simula un Garbage collector
/// @author Jose
///
class GarbageCollector{

public:

    ///
    /// @brief Metodo que inicializa el thread de la clase
    /// @author Jose
    ///
    void GCInit();

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
    void update (int ref);

    ///
    /// @brief Metodo que se ejecuta cuando un VSPtr es eliminado
    /// @param La direccion de memoria de un VSPtr
    /// @author Jose
    ///
    void clear(int ref);

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
    void GCInitImp();

    ///
    /// @brief Metodo que se ejecuta en el thread, busca aquellos VSPtr cuya referencia es 0
    /// @author Jose
    ///
    void inspect();

    ///
    /// @brief Implemetacion de update
    /// @author Jose
    ///
    void updateImp (int ref);

    ///
    /// @brief Genera un ID para un nuevo VSPtr con base en IDref
    /// @author Jose
    ///
    int generateID();

    ///
    /// @brief Implemetacion de clear
    /// @author Jose
    ///
    void clearImp(int ref);

    ///
    /// @brief Accede a la lista enlazada y busca los datos del VSPointr cuya dir de memoria sea igual a ref
    /// @param La direccion de memoria de un VSPtr
    /// @return Un array con los datos del VSPtr
    /// @author Jose
    ///
    int* searchByRef(int ref);


};