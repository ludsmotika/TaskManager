#include "User.h"
#include "Dashboard.h"

User::User(MyString username, MyString password) :username(username), password(password) {}

const MyString& User::getUsername() const
{
	return this->username;
}

const MyString& User::getPassword() const
{
	return this->password;
}

const Vector<unsigned>& User::getTasksIds() const
{
	return this->tasksIds;
}

void User::setTasksIds(const Vector<unsigned>& ids)
{
	for (size_t i = 0; i < ids.size(); i++)
		tasksIds.push_back(ids[i]);
}

void User::addTaskId(unsigned id)
{
	tasksIds.push_back(id);
}

bool User::isOwnerOfTheTaskById(unsigned taskId)
{
	for (size_t i = 0; i < tasksIds.size(); i++)
	{
		if (taskId == tasksIds[i])
			return true;
	}

	return false;
}


unsigned User::getDashboardTasksIdsCount() const
{
	return dashboard.getTasksCount();
}

const Dashboard& User::getDashboard() const
{
	return this->dashboard;
}

void User::addTaskToDashboard(SharedPtr<Task> task)
{
	dashboard.addTask(task);
}

void User::removeTaskId(unsigned taskId)
{
	for (size_t i = 0; i < tasksIds.size(); i++)
	{
		if (tasksIds[i] == taskId)
		{
			tasksIds.erase(i);
			break;
		}
	}
}
