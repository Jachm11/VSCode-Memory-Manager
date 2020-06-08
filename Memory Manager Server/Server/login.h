#include <iostream>
using namespace std;

#include "linkedlist.cpp"

class Login
{
    private:
    
        string password;//= "8d4ce490f740cc9b6d50a2bc33625797";
        

    public:
        Login();
        bool checkPassword(string attempt);
        


};

class User : public Login
{
    private:

        int socketNumb;
        bool access;
        string pointerInfo;
        LinkedList<string> pointerData;
    public:
        User();
        User(int socket);
        void addData(string ptrData);
        bool tryPassword(string attempt);
        int getSocketNumb();
        bool getAccess();
        void setAccess(bool acc);
        LinkedList<string> getPointerData();
        void setPointerInfo(string info); 
        string getPointerInfo();
};