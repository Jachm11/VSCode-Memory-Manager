#include "Garbage Collector.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <future>
#include <typeinfo>
#include <vector>

std::vector<std::future<void>> thread_thing;

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
    std::cout<<"GC is ON"<<std::endl;
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
void GarbageCollector :: newPtr(VSPtr<T>* VSDir,void* TDir){
    getInstance()->newPtrImp(VSDir,TDir);
}

template <class T>
void GarbageCollector :: newPtrImp(VSPtr<T>* VSDir,void* TDir){

    VSPointers newPointer;
    newPointer.dir = VSDir;
    newPointer.ID = (VSDir)->getIDref();
    getInstance()->VSptrs.insertFirst(newPointer);
    std::cout<< "New VSPointer added in GC"<<std::endl;

    VSData* DataInfo = searchInData(TDir);
    if (DataInfo == NULL){
        std::cout<< "New variable added in GC"<<std::endl;
        VSData newVar;
        newVar.dir = TDir;
        newVar.refs = 1;
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
            if ( data->dir == ref){ //talvez casteo necesario
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


