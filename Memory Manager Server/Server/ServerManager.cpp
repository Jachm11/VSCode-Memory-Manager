#include <iostream>
using namespace std;
#include "ServerManager.h"

//#include "json.hpp"
//using namespace nlohmann;

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
bool ServerManager::checkId(string ptrData, string ptrId)
{
   //string ptrData ="{\ntipo:3,\nvalor:4,\nid:3246766\n}";
    for(int i =0;i<3;i++)
    {
        ptrData=ptrData.substr(ptrData.find("\n")+2);
    }
    ptrData=ptrData.substr(0, ptrData.find("}")-3);
    ptrData= ptrData.substr(3);
    //cout <<ptrData << endl;
    if(ptrData==ptrId)
    {
        return true; 
    }
    else
    {
        return false;
    }
    
}

string ServerManager::getPtrById(string allPtr, string id)
{
    //string allPtr= "{\ntipo:3,\nvalor:4,\nid:3246766\n},\ntipo:1,\nvalor:6,\nid:76766\n},\ntipo:0,\nvalor:4,\nid:653\n},\ntipo:ib,\nvalor:54,\nid:vb\n}";    
    //string p= "{\ntipo:3,\nvalor:4,\nid:3246766\n},";
	int count = 0;
	for (int i = 0; (i = allPtr.find("}", i)) !=string::npos; i++) {
		count++;
	}
    if(checkId(allPtr.substr(0,allPtr.find("}")),id))
    {
        //return "yes";
        return ptrFeo(allPtr.substr(0,allPtr.find("}")));
    }
    else
    {
        
        for(int k=1;k<count;k++){
            string allPtrtemp=allPtr;
        // para conseguir cada puntero despues del primero
            for(int i =0;i<3*k;i++)
            {
                allPtrtemp=allPtrtemp.substr(allPtrtemp.find(",")+3);
            }
            allPtrtemp=allPtrtemp.substr(0, allPtrtemp.find("}")-3);
            allPtrtemp="{"+allPtrtemp+"\n}";
            //cout << p.size() <<endl;
            //cout << allPtrtemp <<endl;
            if (checkId(allPtrtemp,id))
            {
                return ptrFeo(allPtrtemp);
                //return allPtrtemp;
            }
        }
    }
    return "notfound";
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
string ServerManager::ptrFeo(string ptrLindo)
{
    //{\ntipo:3,\nvalor:4,\nid:3246766\n}
    string ptrFeo;
    ptrLindo=ptrLindo.substr(2);
    ptrLindo.pop_back();
    ptrLindo.pop_back();
    ptrLindo.replace(ptrLindo.find(","),2,".");
    ptrLindo.replace(ptrLindo.find(","),2,".");
    //ptrFeo= ptrLindo.erase(ptrLindo.find("\n"));
    //ptrFeo= ptrFeo+ptrLindo.erase(ptrLindo.find("\n"));
    return ptrLindo;
}

string ServerManager::newGetPtr(string allPtr, string id)
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
        
        newPtr=newPtr+ptrFeo(current)+";";
        allPtr="{"+allPtr.substr(allPtr.find("}")+2);
        count=count-1;
    } 
    
    return newPtr; 

}
string ServerManager::idResponse(string ptrId, int socket)
{

    Node<User> *temp = getUserBySocket(socket);
    User usertemp= *temp->getData();
    if (usertemp.getPointerInfo()=="")
    {
        return "noptrs";
    }
    return getPtrById(usertemp.getPointerInfo(),ptrId);

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
        else if(clientRequest.at(0)=='i')// && clientRequest.at(1)=='d')
        {
            if (usertemp.getPointerInfo()== ""){return "noptrs";}
            //return "Solicito id";
            //cout << clientRequest.substr(3)<< endl;
            return "{\ntipo:3,\nvalor:4,\nid:3246766\n}";
            
            
            //return idResponse(clientRequest.substr(3), socket);
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

