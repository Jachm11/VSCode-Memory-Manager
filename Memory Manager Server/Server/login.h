#include <iostream>
using namespace std;

#include "linkedlist.cpp"
///
/// @brief  Clase que guarda la contraseña del servidor y verifica si está correcta
/// @author Natalia
class Login
{
    private:
        string password;//= "8d4ce490f740cc9b6d50a2bc33625797";
        ///
        /// @brief Costructor de Login
        /// @author Natalia
        Login();
        
        

    public:
        bool checkPassword(string attempt);
        


};

class User : public Login
{
    private:

        int socketNumb;
        bool access;
        string pointerInfo;
        LinkedList<string> pointerData;
    public:
        User();
        User(int socket);
        void addData(string ptrData);
        bool tryPassword(string attempt);
        int getSocketNumb();
        bool getAccess();
        void setAccess(bool acc);
        LinkedList<string> getPointerData();
        void setPointerInfo(string info); 
        string getPointerInfo();
};