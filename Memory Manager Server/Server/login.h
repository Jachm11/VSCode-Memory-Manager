#include <iostream>
using namespace std;

#include "linkedlist.cpp"
///
/// @brief  Clase que guarda la contraseña del servidor y verifica si esta correcta
/// @author Natalia
class Login
{
    private:
        string password;

        
        
        

    public:
        ///
        /// @brief 
        /// @param 
        /// @return 
        /// @author Natalia
        ///
        bool checkPassword(string attempt);
        ///
        /// @brief Costructor de Login
        /// @author Natalia
        Login();


};
///
/// @brief Clase que crea un usuario en el servidor
/// @author Natalia
///
class User : public Login
{
    private:

        int socketNumb;
        bool access;
        string pointerInfo;
    public:
        ///
        /// @brief Constructor de la clase User sin parametros
        /// @author Natalia
        ///
        User();
        ///
        /// @brief Constructor de la clase User asignando el numero de socket
        /// @author Natalia
        ///
        User(int socket);
        ///
        /// @brief Verifica si la contraseña que escribio el usuario es valida y cambia la variable de acceso inicialmente en false
        /// @param intento 
        /// @return true si es correcta, false de lo contrario
        /// @author Natalia
        ///
        bool tryPassword(string attempt);
        ///
        /// @brief Retorna el numero de socket
        /// @return socketNumb
        /// @author Natalia
        ///
        int getSocketNumb();
        ///
        /// @brief Retorna la informacion de los punteros
        /// @return pointerInfo
        /// @author Natalia
        ///
        string getPointerInfo();
        ///
        /// @brief Retorna si el usuario tiene acceso o no
        /// @return access
        /// @author Natalia
        ///
        bool getAccess();
        
        ///
        /// @brief Asigna el valor de la informacion de los punteros
        /// @param info de los punteros
        /// @author Natalia
        ///
        void setPointerInfo(string info); 
};
        