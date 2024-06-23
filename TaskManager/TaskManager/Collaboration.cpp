#include "Collaboration.h"
#include "MyString.h"

Collaboration::Collaboration(unsigned id, MyString name, MyString creator)
{
	this->id = id;
	this->name = name;
	this->creator = creator;
}

bool Collaboration::isCreatorOfCollaboration(const User& user) const
{
	if (creator == user.getUsername())
		return true;

	return false;
}

bool Collaboration::isUserPartOfCollaboration(const User& user) const
{
	for (size_t i = 0; i < workingUsers.getUsersCount(); i++)
	{
		if (user.getUsername() == workingUsers[i].getUsername())
			return true;
	}
	return false;
}

void Collaboration::addUser(const User& user)
{
	bool isUserAlreadyInCollaboration = false;

	for (size_t i = 0; i < workingUsers.getUsersCount(); i++)
	{
		if (workingUsers[i]->getUsername() == user.getUsername())
			isUserAlreadyInCollaboration = true;
	}

	if (!isUserAlreadyInCollaboration)
		workingUsers.addUser(user);
}

void Collaboration::printTasks() const
{
	if (tasks.getTasksCount() == 0)
		throw std::invalid_argument("There aren't any tasks in this collaboration!");

	for (size_t i = 0; i < tasks.getTasksCount(); i++)
		tasks[i].print();
}

void Collaboration::removeTasksForUsers(UsersCollection& users)
{
	for (size_t i = 0; i < tasks.getTasksCount(); i++)
	{
		for (size_t j = 0; j < users.getUsersCount(); j++)
		{
			if (((CollaborationTask*)tasks[i].operator->())->getAssignee() == users[j]->getUsername())
				users[j]->removeTaskId(tasks[i]->getId());
		}

	}
}

void Collaboration::addCollaborationTask(CollaborationTask* task)
{
	tasks.addTask(task);
}

bool Collaboration::isTaskAlreadyInTheCollaboration(MyString username, MyString taskName, time_t taskDueDate, MyString taskDescription)
{
	for (size_t i = 0; i < tasks.getTasksCount(); i++)
	{
		SharedPtr<CollaborationTask> currentTask = (CollaborationTask*)(tasks[i].operator->());
		if (currentTask->getAssignee() == username && currentTask->getName() == taskName && currentTask->getDueDate() == taskDueDate && currentTask->getDescription() == taskDescription)
			return true;
	}

	return false;
}


unsigned Collaboration::getId() const
{
	return id;
}

MyString Collaboration::getName() const
{
	return name;
}

MyString Collaboration::getCreatorName() const
{
	return creator;
}
