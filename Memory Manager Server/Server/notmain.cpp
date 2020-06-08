
#include <iostream>
using namespace std;
#include "ServerManager.cpp"

#include <sstream>

#include <sstream>


#include "json.hpp"
using namespace nlohmann;


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
    cout <<manager.serverResponse("{hdasjkhk}", 1)<<endl;//envie un json y ya tengo acceso
    cout <<manager.serverResponse("id hdasjkhk", 1)<<endl;//pedi una id  y ya tengo acceso
    cout <<manager.serverResponse("asjkhk", 1)<<endl;// esto no lo recibe

    
    //cout << manager.getUserBySocket(3).getSocketNumb();
    //cout << usr1.getSocketNumb();
   
    
   

    return 0;
}