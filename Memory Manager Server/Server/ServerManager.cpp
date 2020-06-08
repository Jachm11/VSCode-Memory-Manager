#include <iostream>
using namespace std;
#include "ServerManager.h"

#include "json.hpp"
using namespace nlohmann;

Node<User>* ServerManager::getUserBySocket(int socket)
{
    if (users.getHead()==NULL){
        std::cout <<"null list";
    }else{
        Node<User> *current = users.getHead();
        
        while (current != NULL) {
            User usertemp=*current->getData();
            if(usertemp.getSocketNumb()==socket)
            {
                return current;
            }
            current = current->getNext();
        }
    }
    cout << "what"<<endl;

}
bool ServerManager::hasAccess(int socket)
{
    //User usertemp = getUserBySocket(socket);
    return false;
    
    

}
bool ServerManager::checkId(string ptrInfo, string ptrId)
{
    // separar el string para obtener solo el id
}
int ServerManager::getPtrIndex(Node<User>* user, string id)
{
    
}

string ServerManager::passwordResponse(string attempt, int socket)
{
    Node<User> *temp = getUserBySocket(socket);
    
    User usertemp= *temp->getData();
    
    if (!usertemp.getAccess())
    {
        if (usertemp.tryPassword(attempt))
        {
            //usertemp.setAccess(true);
            getUserBySocket(socket)->setData(usertemp);
            
            
            return "Access granted";
        }
        else
        {
            return "Incorrect password, try again with command: p 'password' ";

        }


    }
    else
    {
        return "You already had access to server";
    }
    
}

string ServerManager::jsonResponse(string ptrInfo, int socket)
{
    Node<User> *temp = getUserBySocket(socket);
    User usertemp= *temp->getData();
    usertemp.setPointerInfo(ptrInfo);
    getUserBySocket(socket)->setData(usertemp);
    
    return ptrInfo;
    

}
string ServerManager::idResponse(string clientRequest,string ptrId, int socket)
{
    json jsonObj=json::parse(clientRequest);
    
    cout << jsonObj["tipo"];

}


void ServerManager::addUser(User newUser)
{
    users.insertFirst(newUser);
}

string ServerManager::serverResponse(string clientRequest, int socket)
{
    Node<User> *temp = getUserBySocket(socket);
    User usertemp= *temp->getData();
    if(clientRequest.at(0)=='p')
    {
        //cout << "Escribio contraseña" << endl;
        return passwordResponse(clientRequest.substr(2,clientRequest.max_size()), socket);
        
    }
    if(usertemp.getAccess()){
        if(clientRequest.at(0)=='{')
        {
            //cout << "Envio json" << endl;
            return jsonResponse(clientRequest,socket);
        }
        else if(clientRequest.at(0)=='i' && clientRequest.at(1)=='d')
        {
            //cout << "Solicito id"<< endl;
            return idResponse(clientRequest,"id", socket);
        }
        else
        {
            return "Command not recognized";
        }
        
    }
    else
    {
        return "You don't have access to server, try writing the password with command: p 'password' ";
    }
    

}
