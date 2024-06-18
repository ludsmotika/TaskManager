#pragma once
#include "UsersCollection.h"
#include "Dashboard.h"

//TODO: think about the dashBoard and where the logic for it should be
class Session 
{
public:
    static Session& getInstance();

    void init(const char* usersFilename, const char* tasksFilename, const char* collaborationsFilename);

    void registerUser(MyString username, MyString password);
    void loginUser(MyString username, MyString password);

    void addTask(MyString name, time_t dueDate, MyString description);

    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;

private:
    Session();

    UsersCollection usersCollection;
    TasksCollection tasksCollection;
    Dashboard dashboard;
    int currentUserIndex = -1;

    MyString usersFilename;
    MyString tasksFilename;
    MyString collaborationsFilename;

    bool initialized;

    void saveUserToFile(const User& user) const;
};