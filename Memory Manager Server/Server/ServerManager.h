#include <iostream>
using namespace std;
#include "login.cpp"

class ServerManager
{
    private:
        

        bool hasAccess(int socket);
        string passwordResponse(string attempt, int socket);//responde si esta correcta o incorrecta
        string jsonResponse(string ptrInfo, int socket);// responde con el ID que se le asigna
        string idResponse(string ptrId, int socket);// responde con el json del puntero con el ID solicitado
        Node<User>* getUserBySocket(int socket);
        bool checkId(string ptrInfo, string ptrId);
        string getPtrById(string allPtr, string id);
        string ptrFeo(string ptrLindo);
        string newGetPtr(string allPtr, string id);
        
    public:
        LinkedList<User> users;
        
        void addUser(User newUser);
        //casos: 
        //envia p y password, responde ok o no 
        // envía { json, responde ID
        //envía id ID, responde con json
        string serverResponse(string clientRequest, int socket);
        
        
        
        
};