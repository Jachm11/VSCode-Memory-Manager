#include <iostream>


class holas{

public:
    int dato = 5;

    int* ptrdato = &dato;

};

int main(){

    int hola = 5;

    int* holaptr = &hola;

    holas clase;


    std:: cout << "Hello world" << std::endl ;

    std:: cout << hola << std::endl ;

    std:: cout << &hola << std::endl ;

    std:: cout << holaptr << std::endl ;

    holas* temp = &clase;
    free(temp);


    std:: cout << holaptr << std::endl ;

    std:: cout << clase.dato << std::endl ;

    //std:: cout << holaptr << std::endl ;



    return 0;
}