#include <iostream>
using namespace std;
#include "ServerManager.h"


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

int ServerManager::getUserIndex(int socket)
{
    if (users.getHead()==NULL){
        std::cout <<"null list";
    }else{
        Node<User> *current = users.getHead();
        int count=0;
        while (current != NULL) {
            User usertemp=*current->getData();
            if(usertemp.getSocketNumb()==socket)
            {
                return count;
            }
            current = current->getNext();
            count++;
        }
        return count;
    }
    cout << "what"<<endl;

}


string ServerManager::toJson(string ptr)
{
    string json="{\n";
    for(int i=0;i<2;i++){
    json= json+ ptr.substr(0,ptr.find("."))+",\n";
    ptr =ptr.substr(ptr.find(".")+1);
    }
    json= json+ptr+"\n}";
    return json;
    

}

string ServerManager::ptrFormat(string ptr)
{
    
    ptr=ptr.substr(2);
    ptr.pop_back();
    ptr.pop_back();
    ptr.replace(ptr.find(","),2,".");
    ptr.replace(ptr.find(","),2,".");
    ptr= ptr.substr(1);
    ptr.pop_back();
    ptr.replace(ptr.find("."),2,"+");
    ptr.replace(ptr.find("."),2,".");
    ptr.replace(ptr.find("+"),1,".");

    return ptr;
}
string ServerManager::getIdfromPtr(string ptr)
{
    for(int i=0;i<3;i++)
    {
        ptr=ptr.substr(ptr.find(":")+1);
    }
    return ptr;
}

string ServerManager::getPtr(string allPtr, string id)
{
        
   
    int count = 0;
	for (int i = 0; (i = allPtr.find("}", i)) !=string::npos; i++) {
		count++;
	} 
    string newPtr;
    while(count-1!=0)
    {
        
        string current=allPtr;
        current= current.substr(0, current.find("}")+1);
        
        newPtr=newPtr+ptrFormat(current)+";";
        allPtr="{"+allPtr.substr(allPtr.find("}")+2);
        if (getIdfromPtr(ptrFormat(current)).compare(id)==0){return toJson(ptrFormat(current));}
        count=count-1;
    } 
        string current=allPtr;
        current= current.substr(0, current.find("}")+1);
        
        newPtr=newPtr+ptrFormat(current)+";";
        if (getIdfromPtr(ptrFormat(current)).compare(id)==0){return toJson(ptrFormat(current));}
    
    return "notfound";
    

}
string ServerManager::idResponse(string ptrId, int socket)
{

    Node<User> *temp = getUserBySocket(socket);
    User usertemp= *temp->getData();
    if (usertemp.getPointerInfo()=="")
    {
        return "noptrs";
    }
    return getPtr(usertemp.getPointerInfo(),ptrId);

}
string ServerManager::passwordResponse(string attempt, int socket)
{
    Node<User> *temp = getUserBySocket(socket);
    
    User usertemp= *temp->getData();
    
    if (!usertemp.getAccess())
    {
        if (usertemp.tryPassword(attempt))
        {
            getUserBySocket(socket)->setData(usertemp);
            
            
            return "goodpass";
        }
        else
        {
            return "badpass";

        }


    }
    else
    {
        return "hasaccess";
    }
    
}

string ServerManager::jsonResponse(string ptrInfo, int socket)
{
    Node<User> *temp = getUserBySocket(socket);
    User usertemp= *temp->getData();
    usertemp.setPointerInfo(ptrInfo);
    getUserBySocket(socket)->setData(usertemp);
    
    return "ptrssaved";
    

}


void ServerManager::addUser(User newUser)
{
    users.insertFirst(newUser);
}

void ServerManager::deleteUser(int socket)
{
   
    users.deleteByIndex(getUserIndex(socket));
    
}
string ServerManager::serverResponse(string clientRequest, int socket)
{
    Node<User> *temp = getUserBySocket(socket);
    User usertemp= *temp->getData();
    if(clientRequest.at(0)=='p')
    {
        return passwordResponse(clientRequest.substr(2,clientRequest.max_size()), socket);
        
    }
    if(usertemp.getAccess()){
        if(clientRequest.at(0)=='{')
        {
            return jsonResponse(clientRequest,socket);
        }
        else if(clientRequest.at(0)=='i')
        {
            if (usertemp.getPointerInfo()== ""){return "noptrs";}                      
            return idResponse(clientRequest.substr(3), socket);
        }
        else
        {
            return "notrecognized";
        }
        
    }
    else
    {
        return "noaccess";
    }
    

}

