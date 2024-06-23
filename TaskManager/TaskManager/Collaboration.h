#pragma once
#include "UsersCollection.h";
#include "TasksCollection.h";
#include "CollaborationTask.h";

class Collaboration
{
public:

	Collaboration(unsigned id, MyString name, MyString creator);

	unsigned getId() const;
	MyString getName() const;
	MyString getCreatorName() const;

	bool isCreatorOfCollaboration(const User& user) const;
	bool isUserPartOfCollaboration(const User& user) const;
	bool isTaskAlreadyInTheCollaboration(MyString username, MyString taskName, time_t taskDueDate, MyString taskDescription);

	void addCollaborationTask(CollaborationTask* task);

	void removeTasksForUsers(UsersCollection& users);

	void addUser(const User& user);
	void printTasks() const;
private:
	unsigned id;
	MyString name;
	MyString creator;
	UsersCollection workingUsers;

	TasksCollection tasks;
};