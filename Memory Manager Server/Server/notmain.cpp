
#include <iostream>
using namespace std;
#include "ServerManager.cpp"

#include <sstream>

#include <sstream>


string ptrFeo(string ptrLindo)
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
string newGetPtr(string allPtr, string id)
{
    //string allPtr= "{\ntipo:3,\nvalor:4,\nid:3246766\n},\ntipo:1,\nvalor:6,\nid:76766\n},\ntipo:0,\nvalor:4,\nid:653\n},\ntipo:ib,\nvalor:54,\nid:vb\n}";    
   
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
bool ptrExists(string allPtrs, string id)
{
    
    if(allPtrs.rfind(id)== std::string::npos)
    {
        return false;
    }
    else
    {
        return true;
    }
    
}

int main(int argc , char *argv[])
{
    
   
    User usr= User(0);
    User usr1= User(1);
    User usr2= User(2);
    User usr3= User(3);
    
    
    ServerManager manager;
    manager.addUser(usr);
    manager.addUser(usr2);
    manager.addUser(usr3);
    manager.addUser(usr1);
    cout << manager.serverResponse("p ugfeugfe", 1)<<endl;//escribi una contraseña mala(no tengo acceso)
    cout <<manager.serverResponse("{json json json}", 1)<<endl;//trate de enviar un json(sin acceso)
    cout <<manager.serverResponse("id lo que sea", 1)<<endl;//trate de pedir una id(sin acceso)
    cout << manager.serverResponse("p suryrulz", 1)<<endl;//contraseñacorrecta (ya tengo acceso)
    cout << manager.serverResponse("p suryrulz", 1)<<endl;
    cout <<manager.serverResponse("{\ntipo:3,\nvalor:4,\nid:3246766\n},\ntipo:1,\nvalor:6,\nid:76766\n},\ntipo:0,\nvalor:4,\nid:653\n},\ntipo:ib,\nvalor:54,\nid:vb\n}", 1)<<endl;//envie un json y ya tengo acceso
    cout <<manager.serverResponse("id hdasjkhk", 1)<<endl;//pedi una id  y ya tengo acceso
    cout <<manager.serverResponse("id vb", 1)<<endl;
    cout <<manager.serverResponse("id 3246766", 1)<<endl;// esto no lo recibe
    cout << "------------------"<<endl;
    //cout << ptrFeo("{\ntipo:3,\nvalor:4,\nid:3246766\n}")<< endl;
    
    
   

    return 0;
}
