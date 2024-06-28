#pragma once
#include "UsersCollection.h";
#include "TasksCollection.h";
#include "CollaborationTask.h";
#include <fstream>

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

	void addCollaborationTask(const SharedPtr<Task>& task);
<<<<<<< HEAD
=======
	void addCollaborationTask(const Task& task);
>>>>>>> parent of a65ba37 (refactoring to work with ids)

	void removeTasksForUsers(UsersCollection& users);

	void addUser(User user);
	void printTasks() const;

	const UsersCollection& getWorkingUsers() const;

	void saveToFile(std::ofstream& os);
private:
	unsigned id;
	MyString name;
	MyString creator;
	UsersCollection workingUsers;

	TasksCollection tasks;
};