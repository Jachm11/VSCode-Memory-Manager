#include "Garbage Collector.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <future>
#include <typeinfo>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>



std::vector<std::future<void>> thread_thing;
std::vector<std::future<void>> thread_thing2;

GarbageCollector :: GarbageCollector(){
    IDref = 0;
}

void GarbageCollector :: GCInit(){
    if (getInstance()->init == false){
        getInstance()->GCInitImp();
        getInstance()->init = true;
    }
}

void GarbageCollector :: GCInitImp(){

    thread_thing.push_back(std::async(std::launch::async,inspect));
    thread_thing2.push_back(std::async(std::launch::async,startServer));
    std::cout<<"GC is ON"<<std::endl;
}

void GarbageCollector :: startServer(){
    //Crear el socket
    int srv_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (srv_socket == -1){
        cerr << "No se pudo crear el socket";
        //return -1;
    }

    // Ligar (bind) a un puerto o IP
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000); //host to network short
    inet_pton(AF_INET,"0.0.0.0",&hint.sin_addr);

    if (bind(srv_socket,(sockaddr*) &hint, sizeof(hint)) == -1){
         cerr << "No se pudo enlazar al IP/puerto" <<endl;
         //return -2;
    }


    // Poner el socket a escuchar
    if(listen(srv_socket, SOMAXCONN) == -1){
        cerr << "Not srv_socket" ;
    }

    // Aceptar llamadas
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host [NI_MAXHOST];
    char svc[NI_MAXSERV];

    int clt_socket = accept(srv_socket,(sockaddr*)&client,&clientSize);

    if (clt_socket == -1) {
        cerr << "Promeblemas con el cliente";
    } else{
        cout << "Conexion con cliente establecida exitosamente!\n";
    }
    

    char buffer [4096] = {0};

    while (true){
        memset(buffer,0,4096);
        int bytesRecv = read(clt_socket,buffer,4096);
        if (bytesRecv == -1){
            cerr << "Hubo un error de conexion" << endl;
            break;
        }

        if (bytesRecv == 0){
            cout << "El cliente se ha desconectado" << endl;
            break;
        }
        cout << buffer[0] << endl; //print mesaje que llega


        if ((int)buffer[0] - 48 == 1){

            string res = dataTosend();

            send(clt_socket,res.c_str(),res.size(), 0 );

        }else if((int)buffer[0] - 48 == 2){

            string res = toJson();

            send(clt_socket,res.c_str(),res.size(), 0 );
            
        }else{
            send(clt_socket,"ERROR",5, 0 );
        }

    }

    close(clt_socket);
    close(srv_socket);
    startServer();
}

string GarbageCollector :: dataTosend(){
    string tipo;
    string valor;
    string dir;
    string ref;
    string info;

    if (getInstance()->Data.getHead() != 0 ){
        for(int i = 0; i < getInstance()->Data.getSize(); i++){

            VSData* dato = getInstance()->Data.searchByIndex(i)->getData();
            tipo = dato->tipo;
            dir = to_string((long)dato->dir);
            ref = to_string(dato->refs);

            if (tipo == "int") 
                valor = to_string((*(int*)dato->dir));
            else if(tipo == "double")
                valor = to_string((*(double*)dato->dir));
            else if(tipo == "char")
                valor = to_string((*(char*)dato->dir));
            else if(tipo == "string")
                valor = (*(string*)dato->dir);
            else if(tipo == "bool")
                valor = to_string((*(bool*)dato->dir));
            else if(tipo == "float")
                valor = to_string((*(float*)dato->dir));
            else if(tipo == "short")
                valor = to_string((*(short*)dato->dir));
            else if(tipo == "unsingned")
                valor = to_string((*(unsigned*)dato->dir));
            else{
                valor = "object";
            }
            info = info + tipo + "," + valor + "," + dir + "," + ref+";";
        }
        return info;
    }
    return "vacio";

}

string GarbageCollector :: toJson(){
    string json = "{\n";
    for(int i = 0; i < getInstance()->VSptrs.getSize(); i++){
        VSPointers* pointer = getInstance()->VSptrs.searchByIndex(i)->getData();

        string tipo = pointer->tipo;
        string ID = to_string( pointer->ID);

        string valor;
        if (tipo == "int")
                valor = to_string((*(int*)pointer->dato));
            else if(tipo == "double")
                valor = to_string((*(double*)pointer->dato));
            else if(tipo == "char")
                valor = to_string((*(char*)pointer->dato));
            else if(tipo == "string")
                valor = (*(string*)pointer->dato);
            else if(tipo == "bool")
                valor = to_string((*(bool*)pointer->dato));
            else if(tipo == "float")
                valor = to_string((*(float*)pointer->dato));
            else if(tipo == "short")
                valor = to_string((*(short*)pointer->dato));
            else if(tipo == "unsigned")
                valor = to_string((*(unsigned*)pointer->dato));
            else{
                valor = "object";
            }

            string type = "tipo";
            string value = "valor";
            string id = "id";

        //json = json + '"' + type + '"'+  ":" + '"' + tipo + '"'+","+ "\n" +'"' + value + '"'+  ":" + '"' + valor + '"'+","+ "\n" + '"' + id + '"' +  ":" + '"' + ID + '"'+ "\n},\n"  ;
        json = json + type +  ":" + tipo +","+ "\n" + value +  ":"  + valor +","+ "\n" + id +  ":"  + ID + "\n},\n"  ;
    }
    if(!json.empty()){
        return json.substr(0,json.size()-2);
    }else{
        return "error";
    }

}


void GarbageCollector :: inspect(){

    while(true){
        sleep(3);
        std::cout<<"searching..."<<std::endl;
        
        if (getInstance()->Data.getHead() != 0 ){
            for(int i = 0; i < getInstance()->Data.getSize(); i++){
                VSData* dato = getInstance()->Data.searchByIndex(i)->getData();
                if ( dato->refs  <= 0){
                    delete((decltype(dato->dir)*)dato->dir);
                    getInstance()->Data.deleteByIndex(i);
                    i--;
                    std::cout<<"GC deleted a unreferenced varible"<<std::endl;
                }
            }
        }   
    }
}

GarbageCollector* GarbageCollector :: getInstance(){
    static GarbageCollector instance;
    return &instance;
}

template <class T>
void GarbageCollector :: newPtr(VSPtr<T>* VSDir,void* TDir,string tipo){
    getInstance()->newPtrImp(VSDir,TDir,tipo);
}

template <class T>
void GarbageCollector :: newPtrImp(VSPtr<T>* VSDir,void* TDir,string tipo){

    VSPointers newPointer;
    newPointer.dir = VSDir;
    newPointer.ID = (VSDir)->getIDref();
    newPointer.tipo = tipo;
    newPointer.dato = TDir;
    getInstance()->VSptrs.insertFirst(newPointer);
    std::cout<< "New VSPointer added in GC"<<std::endl;

    VSData* DataInfo = searchInData(TDir);
    if (DataInfo == NULL){
        std::cout<< "New variable added in GC"<<std::endl;
        VSData newVar;
        newVar.dir = TDir;
        newVar.refs = 1;
        newVar.tipo = tipo;
        getInstance()->Data.insertFirst(newVar);
    }else{
        DataInfo->refs++;
        std::cout<< "Active references of: "<<DataInfo->dir << " increased to: "<< DataInfo->refs<< std::endl;
    }
}

int GarbageCollector :: generateID(){
    int x = getInstance()->IDref;
    getInstance()->IDref++;
    std::cout<< "ID generado es: "<< x <<std::endl;
    return x;
}

template <class T>
void GarbageCollector :: clear(VSPtr<T>* VSDir,void* TDir){
    getInstance()->clearImp(VSDir,TDir);
}

template <class T>
void GarbageCollector :: clearImp(VSPtr<T>* VSDir,void* TDir){

    //Borrar de la lista de VsPtrs
    int pointerDataPos = searchInPtrs(VSDir);
    if (pointerDataPos > 0){
    (getInstance()->VSptrs).deleteByIndex(pointerDataPos);
    std::cout<<"VSPointer succesfully deleted from GC"<<std::endl;
    }else{
        std::cout<<"VSPointer to delete not found"<<std::endl;
    }

    //Decremento de referencias para el dato
    VSData* VarData = searchInData(TDir);
    VarData->refs--;
    std::cout<< "Active references of: "<<VarData->dir << " decreased to: "<< VarData->refs<< std::endl;

}

 VSData* GarbageCollector :: searchInData(void* ref){
    //LinkedList<VSData>* list = &(getInstance()->Data);  
    if (getInstance()->Data.getHead() != 0 ){
        for(int i = 0; i < getInstance()->Data.getSize(); i++){
            VSData* data = getInstance()->Data.searchByIndex(i)->getData();
            if ( data->dir == ref){
                return getInstance()->Data.searchByIndex(i)->getData();
            }
        }
        return NULL;
    }
    return NULL;
}

int GarbageCollector :: searchInPtrs(void* ref){ 
    if (getInstance()->VSptrs.getHead() != 0 ){
        for(int i = 0; i < getInstance()->VSptrs.getSize(); i++){
            VSPointers* pointer = getInstance()->VSptrs.searchByIndex(i)->getData();
            if ( pointer->dir == ref){
                return i;
            }
        }
        return -1;
    }
    return -1;
}


