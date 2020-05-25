#include "Garbage Collector.h"
#include <thread>


GarbageCollector :: GarbageCollector(){
    IDref = 0;
}

void GarbageCollector :: GCInit(){
    if (!init){
        getInstance()->GCInitImp();
        init = true;
    }
}

void GarbageCollector :: GCInitImp(){
    
    std::thread inspector(inspect); 
}

void GarbageCollector :: inspect(){

    using namespace std::literals::chrono_literals;
    
    while(true){
        
        if (VSptrs.getHead() != 0 ){
            for(int i = 0; i <= VSptrs.getSize(); i++){
                int* dato = VSptrs.searchByIndex(i)->getData();
                    if (*(dato+2)  == 0){
                        VSptrs.deleteByIndex(i);
                        i--;
                        std::free((void*)*(dato+1));
                    }
            }
        }
        std::this_thread::sleep_for(5s);
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
        int newPtr [generateID(),ref,1];
        VSptrs.insertFirst(newPtr);
    }
}

int GarbageCollector :: generateID(){
    int x = IDref;
    IDref++;
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
    if (VSptrs.getHead() != 0 ){
        for(int i = 0; i <= VSptrs.getSize(); i++){
            int* dato = VSptrs.searchByIndex(i)->getData();
                if (*(dato+1)  == ref){
                    return dato;
                }
        }
        return NULL;
    }
    return NULL;

}


