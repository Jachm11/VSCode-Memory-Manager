#include "Garbage Collector.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <future>


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
    
    void* arg;
    std::async(std::launch::async,inspect,arg);

    //void* arg;
    //pthread_t inspector;
    //pthread_attr_t attr;
    //pthread_attr_init(&attr);
    //pthread_create(&inspector,&attr,inspect,arg);

    //std::thread inspector(inspect); 
}

void* GarbageCollector :: inspect(void* arg){

    //using namespace std::literals::chrono_literals;
    
    while(true){
        std::cout<<"searching..."<<std::endl;
        
        if (getInstance()->VSptrs.getHead() != 0 ){
            for(int i = 0; i <= getInstance()->VSptrs.getSize(); i++){
                int* dato = getInstance()->VSptrs.searchByIndex(i)->getData();
                    if (*(dato+2)  == 0){
                        getInstance()->VSptrs.deleteByIndex(i);
                        i--;
                        //std::free((void*)*(dato+1));
                    }
            }
        }
        sleep(1);
        
    }

}

GarbageCollector* GarbageCollector :: getInstance(){
    static GarbageCollector instance;
    return &instance;
}

void GarbageCollector :: update(int ref){
    getInstance()->updateImp(ref);
}

void GarbageCollector :: updateImp (int ref){
    int* arr = searchByRef(ref);
    if (arr == NULL){
        int id = generateID();
        int newPtr [3] = {id,ref,1};
        getInstance()->VSptrs.insertFirst(newPtr);
    }
}

int GarbageCollector :: generateID(){
    int x = getInstance()->IDref;
    getInstance()->IDref++;
    return x;
}

void GarbageCollector :: clear(int ref){
    getInstance()->clear(ref);
}

void GarbageCollector :: clearImp(int ref){
    int* arr = searchByRef(ref);
    if (arr != NULL){
        *(arr+2) = 0;
    }
}

int* GarbageCollector :: searchByRef(int ref){
    if (getInstance()->VSptrs.getHead() != 0 ){
        for(int i = 0; i <= getInstance()->VSptrs.getSize(); i++){
            int* dato = getInstance()->VSptrs.searchByIndex(i)->getData();
                if (*(dato+1)  == ref){
                    return dato;
                }
        }
        return NULL;
    }
    return NULL;

}


