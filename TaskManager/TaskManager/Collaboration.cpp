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

void Collaboration::addUser(const SharedPtr<User>& user)
{
	bool isUserAlreadyInCollaboration = false;

	for (size_t i = 0; i < workingUsers.getUsersCount(); i++)
	{
		if (workingUsers[i]->getUsername() == user->getUsername())
			isUserAlreadyInCollaboration = true;
	}

	if (!isUserAlreadyInCollaboration)
		workingUsers.addUser(*user);
}

void Collaboration::printTasks() const 
{
	if (tasks.getTasksCount() == 0)
		throw std::invalid_argument("There aren't any tasks in this collaboration!");

	for (size_t i = 0; i < tasks.getTasksCount(); i++)
		tasks[i].print() ;
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
