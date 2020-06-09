#include <iostream>
using namespace std;
#include "login.cpp"

class ServerManager
{
    private:
        LinkedList<User> users;
        ///
        /// @brief Retorna el nodo de la lista en que se uncuentra el socket con el ID dado por el servidor
        /// @param numero de socket
        /// @return Nodo con el usuario 
        /// @author Natalia
        ///
        Node<User>* getUserBySocket(int socket);

        ///
        /// @brief Retorna la posicion en la lista en la que se encuentra el socket especificado
        /// @param numero de socket
        /// @return indice del usuario el la lista
        /// @author Natalia
        ///
        int getUserIndex(int socket);

        ///
        /// @brief Transforma el formato del string del puntero a Json
        /// @param puntero con el formato tipo:1.valor:6.id:76766
        /// @return puntero con el formato {\ntipo:3,\nvalor:4,\nid:3246766\n}
        /// @author Natalia
        ///
        string toJson(string ptr);

        ///
        /// @brief Transforma el formato del json
        /// @param puntero con el formato {\ntipo:3,\nvalor:4,\nid:3246766\n}
        /// @return puntero con el formato tipo:1.valor:6.id:76766
        /// @author Natalia
        ///
        string ptrFormat(string ptr);

        ///
        /// @brief Obtiene el id aislado de un punter
        /// @param puntero con el formato tipo:1.valor:6.id:76766
        /// @return el dato de id del puntero
        /// @author Natalia
        ///
        string getIdfromPtr(string ptr);

        ///
        /// @brief Retorna los datos del puntero con la id que se solicita
        /// @param allPtrsInfo la informacion de todos los punteros
        /// @param id del puntero que se quiere encontrar
        /// @return La información del puntero solicitado
        /// @author Natalia
        ///
        string getPtr(string allPtr, string id);

        ///
        /// @brief Respuesta cuando se solicita la información de un puntero por id, auxiliar de serverResponse
        /// @param  id solicitada
        /// @param socket que lo solicita
        /// @return json con la información del puntero
        /// @author Natalia
        ///
        string idResponse(string ptrId, int socket);
        ///
        /// @brief Respuesta cuando se escribe la contraseña, auxiliar de serverResponse
        /// @param  intento del usuario de escribir la contraseña
        /// @param socket que lo solicita
        /// @return goodpass si la contraseña es correcta, badpass si es incorrecta y hasaccess si ya tenia acceso
        /// @author Natalia
        ///
        string passwordResponse(string attempt, int socket);
        ///
        /// @brief Respuesta cuando se solicita guardar los punteros en el server, auxiliar de serverResponse
        /// @param  info del puntero que se quiere guardar en forma de json
        /// @param socket que lo solicita
        /// @return ptrsaved cuando guarda la informacion
        /// @author Natalia
        ///
        string jsonResponse(string ptrInfo, int socket);

    public:
        ///
        /// @brief Añade un usuario a la lista de users del server manager
        /// @param usuario que se quiere añadir, inicializado con el socket que el servidor le asigna
        /// @author Natalia
        ///
        void addUser(User newUser);

        ///
        /// @brief Elimina un usuario a la lista de users del server manager
        /// @param socket id del usuario que se quiere eliminar
        /// @author Natalia
        ///
        void deleteUser(int socket);
        ///
        /// @brief Verifica el camndo que llega al servidor y dependiendo de cual es llama a la funcion que contruye la respuesta
        /// @param mensaje del cliente
        /// @param socket que envia el mensaje
        /// @return mensaje segun la respuesta
        /// @author Natalia
        ///
        string serverResponse(string clientRequest, int socket);     
        
};