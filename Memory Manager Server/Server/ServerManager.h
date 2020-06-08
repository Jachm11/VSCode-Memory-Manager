#include <iostream>
using namespace std;
#include "login.cpp"

class ServerManager
{
    private:
        //{\n"tipo":"int",\n"valor":"54",\n"id":"10"\n},\n"tipo":"int",\n"valor":"54",\n"id":"5"\n},\n"tipo":"int",\n"valor":"34",\n"id":"9"\n}
        bool hasAccess(int socket);
        string passwordResponse(string attempt, int socket);//responde si esta correcta o incorrecta
        string jsonResponse(string ptrInfo, int socket);// responde con el ID que se le asigna
        string idResponse(string clientRequest,string ptrId, int socket);// responde con el json del puntero con el ID solicitado
        Node<User>* getUserBySocket(int socket);
        bool checkId(string ptrInfo, string ptrId);
        int getPtrIndex(Node<User>* user, string id);
        
    public:
        LinkedList<User> users;
        
        void addUser(User newUser);
        //casos: 
        //envia p y password, responde ok o no 
        // envía { json, responde ID
        //envía id ID, responde con json
        string serverResponse(string clientRequest, int socket);
        
        
        
        
};