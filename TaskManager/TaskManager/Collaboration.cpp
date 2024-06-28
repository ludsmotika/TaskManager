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

void Collaboration::saveToFile(std::ofstream& os) 
{
	unsigned collaborationId = getId();
	os.write((const char*)&collaborationId, sizeof(unsigned));

	size_t collaborationNameLength = getName().getSize();
	os.write((const char*)&collaborationNameLength, sizeof(size_t));
	os.write(getName().c_str(), sizeof(char) * getName().getSize());

	size_t collaborationCreatorNameLength = getCreatorName().getSize();
	os.write((const char*)&collaborationCreatorNameLength, sizeof(size_t));
	os.write(getCreatorName().c_str(), sizeof(char) * collaborationCreatorNameLength);

	size_t workersCount = workingUsers.getUsersCount();
	os.write((const char*)&workersCount, sizeof(size_t));

	for (size_t i = 0; i < getWorkingUsers().getUsersCount(); i++)
	{
		size_t currentWorkingUserNameLen = workingUsers[i]->getUsername().getSize();
		os.write((const char*)&currentWorkingUserNameLen, sizeof(size_t));
		os.write(workingUsers[i]->getUsername().c_str(), sizeof(char) * currentWorkingUserNameLen);
	}

	size_t tasksCount = tasksIds.size();
	os.write((const char*)&tasksCount, sizeof(size_t));

	for (size_t i = 0; i < tasks.getTasksCount(); i++)
	{
		unsigned currentTaskId = tasksIds[i];
		os.write((const char*)&currentTaskId, sizeof(unsigned));

		/*size_t assigneeNameLen = ((CollaborationTask*)tasks[i].operator->())->getAssignee().getSize();
		os.write((const char*)&assigneeNameLen, sizeof(size_t));
		os.write(((CollaborationTask*)tasks[i].operator->())->getAssignee().c_str(), sizeof(char) * assigneeNameLen);*/
	}
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

void Collaboration::addUser(User user)
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

void Collaboration::printTasks(const TasksCollection& tasks) const
{
	if (tasksIds.size() == 0)
		throw std::invalid_argument("There aren't any tasks in this collaboration!");

	for (size_t i = 0; i < tasksIds.size(); i++)
	{
		if (tasks.getTaskById(tasksIds[i]).isInitlized())
			tasks.getTaskById(tasksIds[i])->print();
	}
}

void Collaboration::removeTasksForUsers(const TasksCollection& tasks, UsersCollection& users)
{
	for (size_t i = 0; i < tasksIds.size(); i++)
	{
		for (size_t j = 0; j < users.getUsersCount(); j++)
		{
			if (((CollaborationTask*)&tasks[tasksIds[i]])->getAssignee() == users[j]->getUsername())
				users[j]->removeTaskId(tasks[i].getId());
		}

	}
}

bool Collaboration::isTaskAlreadyInTheCollaboration(MyString username, MyString taskName, time_t taskDueDate, MyString taskDescription)
{
	for (size_t i = 0; i < tasksIds.size(); i++)
	{
		CollaborationTask* currentTask = (CollaborationTask*)(&tasks[tasksIds[i]]);
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

const UsersCollection& Collaboration::getWorkingUsers() const
{
	return workingUsers;
}

