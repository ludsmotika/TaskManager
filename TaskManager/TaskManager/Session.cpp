#include "Session.h"
#include <fstream>

Session::Session() : initialized(false) {}

Session& Session::getInstance()
{
	static Session session;
	return session;
}

void Session::init(const char* usersFilename, const char* tasksFilename, const char* collaborationsFilename)
{
	if (!initialized)
	{
		this->usersFilename = usersFilename;
		this->tasksFilename = tasksFilename;
		this->collaborationsFilename = collaborationsFilename;

		tasksCollection.readTasksFromFile(tasksFilename);
		usersCollection.readUsersFromFile(usersFilename, tasksCollection);
		//load Collaborations
		initialized = true;
	}
}

void Session::registerUser(MyString username, MyString password)
{
	for (size_t i = 0; i < usersCollection.getUsersCount(); i++)
	{
		if (usersCollection[i]->getUsername() == username)
			throw std::invalid_argument("User with this username already exist!");
	}

	User currentUser(username, password);
	usersCollection.addUser(currentUser);
	currentUserIndex = usersCollection.getUsersCount() - 1;

	this->currentUserIndex = usersCollection.getUsersCount() - 1;
}

void Session::loginUser(MyString username, MyString password)
{
	for (size_t i = 0; i < usersCollection.getUsersCount(); i++)
	{
		if (usersCollection[i]->getUsername() == username && usersCollection[i]->getPassword() == password)
		{
			this->currentUserIndex = i;
			return;
		}
	}

	throw std::invalid_argument("Invalid username or password!");
}

void Session::addTask(MyString name, time_t dueDate, MyString description)
{
	for (size_t i = 0; i < tasksCollection.getTasksCount(); i++)
	{
		if (tasksCollection[i]->getName() == name && tasksCollection[i]->getDueDate() == dueDate)
			throw std::invalid_argument("This task already exists!");
	}

	tasksCollection.addTask(Task(tasksCollection.getTasksCount(), name, dueDate, TaskStatus::ON_HOLD, description));
	usersCollection[currentUserIndex]->addTaskId(tasksCollection.getTasksCount()-1);
}


void Session::updateTaskName(unsigned taskId, MyString newName) 
{
	if (usersCollection[currentUserIndex]->isOwnerOfTheTaskById(taskId))
	{
		tasksCollection.getTaskById(taskId)->setNewName(newName);
	}
	else 
	{
		throw std::invalid_argument("Invalid task id!");
	}
}

void Session::startTaskById(unsigned taskId)
{
	if (usersCollection[currentUserIndex]->isOwnerOfTheTaskById(taskId))
	{
		tasksCollection.getTaskById(taskId)->setNewStatus(TaskStatus::IN_PROCESS);
	}
	else
	{
		throw std::invalid_argument("Invalid task id!");
	}
}

void Session::updateTaskDescription(unsigned taskId, MyString newDescription)
{
	if (usersCollection[currentUserIndex]->isOwnerOfTheTaskById(taskId))
	{
		tasksCollection.getTaskById(taskId)->setNewDescription(newDescription);
	}
	else
	{
		throw std::invalid_argument("Invalid task id!");
	}
}

void Session::logout()
{
	this->currentUserIndex = -1;
	//clear the dashboard
}

bool Session::isThereALoggedInUser() const
{
	return currentUserIndex != -1;
}

void Session::closeSession()
{
	usersCollection.saveAllUserToFile(usersFilename.c_str());
	tasksCollection.saveAllTasksToFile(tasksFilename.c_str());
}