#include <iostream>
using namespace std;
#include "login.h"
#include "md5.cpp"

Login::Login(){

    password = "8d4ce490f740cc9b6d50a2bc33625797";
}
bool Login::checkPassword(string attempt)
{
    if (password== (string)md5(attempt))
    {
        return true;
    }
    else
    {
        return false;
    }
    

}
User::User()
{}

User::User(int socket)
{
    socketNumb=socket;
    access = false;
}

void User::addData(string ptrData)
{
    pointerData.insertLast(ptrData);
}

bool User::tryPassword(string attempt)
{
    if (checkPassword(attempt))
    {
        access = true;
        
        return true;
    }
    else
    {
        access =false;
        
        return false;
    }
    
}

int User::getSocketNumb()
{
    return socketNumb;
}

bool User::getAccess()
{
    return access;
}

void User::setAccess(bool acc)
{
    access = acc;
}

LinkedList<string> User::getPointerData()
{
    return pointerData;
}

void User::setPointerInfo(string info)
{
    pointerInfo=info;
}

string User::getPointerInfo()
{
    return pointerInfo;
}
