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
    void logout();
    void updateTaskName(unsigned taskId, MyString newName);
    void updateTaskDescription(unsigned taskId, MyString newDescription);

    void startTaskById(unsigned taskId);
    void finishTask(unsigned taskId);

    void addTask(MyString name, time_t dueDate, MyString description);
    void addTask(MyString taskName, MyString description);
    void deleteTask(unsigned taskId);

    void getTask(unsigned taskId) const;
    void getTask(MyString taskName) const;

    void listTasks(time_t dueDate) const;
    void listAllTasks() const;
    void listAllCompletedTasks() const;



    void closeSession();

    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;

    bool isThereALoggedInUser() const;

private:
    Session();

    UsersCollection usersCollection;
    TasksCollection tasksCollection;
    int currentUserIndex = -1;

    MyString usersFilename;
    MyString tasksFilename;
    MyString collaborationsFilename;

    bool initialized;

    void initDashBoardForCurrentUser();
};