#include "Garbage Collector.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <future>
#include <typeinfo>


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

    std::async(std::launch::async,inspect);
 
}

void GarbageCollector :: inspect(){

    while(true){
        std::cout<<"searching..."<<std::endl;
        
        if (getInstance()->Data.getHead() != 0 ){
            for(int i = 0; i <= getInstance()->Data.getSize(); i++){
                VSData* dato = getInstance()->Data.searchByIndex(i)->getData();
                if ( dato->refs  <= 0){
                    delete((decltype(dato->dir)*)dato->dir);
                    i--;
                    std::cout<<"Exterminated"<<std::endl;
                }
            }
        }
        sleep(3);   
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
    std::cout<< "Puntero Agregado"<<std::endl;

    VSData* DataInfo = searchInData(TDir);
    if (DataInfo == NULL){
        std::cout<< "Dato Agregado"<<std::endl;
        VSData newVar;
        newVar.dir = TDir;
        newVar.refs = 1;
        getInstance()->Data.insertFirst(newVar);
    }else{
        DataInfo->refs++;
        std::cout<< "Referencia aumentada a: "<<std::endl;
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
    getInstance()->clear(VSDir,TDir);
}

template <class T>
void GarbageCollector :: clearImp(VSPtr<T>* VSDir,void* TDir){

    //Borrar de la lista de VsPtrs
    VSPointers pointerData = *(searchInPtrs(VSDir));
    (getInstance()->VSptrs).deleteByData(pointerData);

    //Decremento de referencias para el dato
    VSData* VarData = searchInData(TDir);
    VarData->refs--;
    std::cout<< "Referencia disminuida a: "<< VarData->refs <<std::endl;

}

 VSData* GarbageCollector :: searchInData(void* ref){
    //LinkedList<VSData>* list = &(getInstance()->Data);  
    if (getInstance()->Data.getHead() != 0 ){
        for(int i = 0; i <= getInstance()->Data.getSize(); i++){
            VSData* data = getInstance()->Data.searchByIndex(i)->getData();
            if ( data->dir == ref){ //talvez casteo necesario
                return getInstance()->Data.searchByIndex(i)->getData();
            }
        }
        return NULL;
    }
    return NULL;
}

VSPointers* GarbageCollector :: searchInPtrs(void* ref){
    //LinkedList<VSPointers>* list = &(getInstance()->VSptrs);  
    if (getInstance()->VSptrs.getHead() != 0 ){
        for(int i = 0; i <= getInstance()->VSptrs.getSize(); i++){
            VSPointers* pointer = getInstance()->VSptrs.searchByIndex(i)->getData();
            if ( pointer->dir == ref){ //talvez casteo necesario
                return getInstance()->VSptrs.searchByIndex(i)->getData();
            }
        }
        return NULL;
    }
    return NULL;
}


