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
                void* arr = (getInstance()->Data.searchByIndex(i)->getData());
                    if (*((int*)arr)  == 0){
                        void* ptr =  (int*)arr; //HAAAAALLLPPPPP
                        getInstance()->Data.deleteByIndex(i);
                        delete(ptr);
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
    int id = generateID();
    void* newVSPtr[2] = {VSDir,&id};
    getInstance()->VSptrs.insertFirst(*newVSPtr);

    void* DataInfo = (searchByRef(TDir,(getInstance()->Data),false))->getData();
    if (DataInfo == NULL){
        int refrences = 1;
        void* newDataInfo[2] = {TDir,&refrences};
        getInstance()->Data.insertFirst(*newDataInfo);
    }

}
template <typename T>
void GarbageCollector :: update(T* oldDir,T* newDir){
    getInstance()->updateImp(oldDir,newDir);
}
template <typename T>
void GarbageCollector :: updateImp (T* oldDir,T* newDir){
    void* oldDato = (searchByRef(oldDir,getInstance()->Data,false))->getData();
    (*((int*)oldDato))--;

    void* newDato = (searchByRef(newDir,getInstance()->Data,false))->getData();
    if (newDato == NULL){
        int refrences = 1;
        void* newDataInfo[2] = {newDir,&refrences};
        getInstance()->Data.insertFirst(*newDataInfo);
    }else{
        (*((int*)newDato))++;
    }
}

int GarbageCollector :: generateID(){
    int x = getInstance()->IDref;
    getInstance()->IDref++;
    return x;
}

template <class T>
void GarbageCollector :: clear(VSPtr<T>* VSDir,void* TDir){
    getInstance()->clear(VSDir,TDir);
}

template <class T>
void GarbageCollector :: clearImp(VSPtr<T>* VSDir,void* TDir){
    //Borrar de la lista de VsPtrs
    void* VSPtrInfo = (searchByRef(VSDir,getInstance()->VSptrs,true))->getData();
    (getInstance()->VSptrs).deleteByData(VSPtrInfo);
    //Decremento de referencias para el dato
    void* DataInfo = (searchByRef(TDir,getInstance()->Data,false))->getData();
    (*((int*)DataInfo))--;
}

//La referecia tiene que estar el primer espacio de lista de cada nodo
 template <typename T>
 Node<void*> GarbageCollector :: searchByRef(T* ref, LinkedList<void*> list,bool VS){
    if (list.getHead() != 0 ){
        for(int i = 0; i <= list.getSize(); i++){
            void* arr = list.searchByIndex(i)->getData();
            if(VS){
                if ( (*(VSPtr<T>*)arr) == (VSPtr<T>*) ref){
                    return list.searchByIndex(i);
                }
            }else{
                if ( (*(T*)arr) == (T*)ref){
                    return list.searchByIndex(i);
                }
            }
        }
        return NULL;
    }
    return NULL;

}


