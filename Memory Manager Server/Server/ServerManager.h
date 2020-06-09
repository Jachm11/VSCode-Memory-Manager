#include <iostream>
using namespace std;
#include "login.cpp"

class ServerManager
{
    private:
        

        LinkedList<User> users;

        Node<User>* getUserBySocket(int socket);
        int getUserIndex(int socket);
        string toJson(string ptr);
        string ptrFormat(string ptr);
        string getIdfromPtr(string ptr);
        string getPtr(string allPtr, string id);
        string idResponse(string ptrId, int socket);
        string passwordResponse(string attempt, int socket);
        string jsonResponse(string ptrInfo, int socket);

    public:
        
        void addUser(User newUser);
        void deleteUser(int socket);
        //casos: 
        //envia p y password, responde ok o no 
        // envía { json, responde ID
        //envía id ID, responde con json
        string serverResponse(string clientRequest, int socket);
        
        
        
        
};