#include"linkedlist.cpp"


void print(int x){

    std::cout<< x << std::endl;

}

void print(char* x){

    std::cout<< x << std::endl;

}

int main(int argc, char const *argv[])
{
    LinkedList<int> hola;
    LinkedList<int> hola2;

    //hola.insertFirst(10);

    std::cout<< hola.getHead() << std::endl;
    std::cout<< hola2.getHead() << std::endl;


    //int var = hola.getHead()->getData();

    //print(var);

    //print(hola.searchByIndex(1)->getData());

    //print(hola.getSize());

    return 0;
}
