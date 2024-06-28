#include "Session.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#pragma warning (disable : 4996)

unsigned Session::id = 0;

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

		try
		{
			tasksCollection.readTasksFromFile(tasksFilename);
			usersCollection.readUsersFromFile(usersFilename, tasksCollection);
			collaborationsCollection.readCollaborationsFromFile(collaborationsFilename, usersCollection, tasksCollection);
		}
		catch (const std::exception&)
		{

		}
		initialized = true;
	}
}

void Session::registerUser(MyString username, MyString password)
{
	if (username == "" || password == "")
		throw std::invalid_argument("Invalid username or password!");

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
			usersCollection[currentUserIndex]->initDashboard(tasksCollection);
			return;
		}
	}

	throw std::invalid_argument("Invalid username or password!");
}

void Session::addTask(MyString name, time_t dueDate, MyString description)
{
	if (name == "" || description == "")
		throw std::invalid_argument("Invalid name or description!");

	Vector<unsigned> tasksIds = usersCollection[currentUserIndex]->getTasksIds();

	for (size_t i = 0; i < tasksIds.size(); i++)
	{
		if (tasksCollection.getTaskById(tasksIds[i])->getName() == name && tasksCollection.getTaskById(tasksIds[i])->getDueDate() == dueDate)
			throw std::invalid_argument("This task already exists!");
	}

	tasksCollection.addTask(Task(id, name, dueDate, TaskStatus::ON_HOLD, description));
	usersCollection[currentUserIndex]->addTaskId(id);

	time_t now = time(nullptr);
	tm* localTime1 = localtime(&now);
	tm* localTime2 = localtime(&now);

	if (localTime1->tm_year == localTime2->tm_year && localTime1->tm_mon == localTime2->tm_mon && localTime1->tm_mday == localTime2->tm_mday)
		usersCollection[currentUserIndex]->addTaskToDashboard(tasksCollection.getTaskById(id));

	id++;
}

void Session::addTask(MyString name, MyString description)
{
	if (name == "" || description == "")
		throw std::invalid_argument("Invalid name or description!");

	Vector<unsigned> tasksIds = usersCollection[currentUserIndex]->getTasksIds();

	for (size_t i = 0; i < tasksIds.size(); i++)
	{
		if (tasksCollection.getTaskById(tasksIds[i])->getName() == name && tasksCollection.getTaskById(tasksIds[i])->getDescription() == description)
			throw std::invalid_argument("This task already exists!");
	}

	tasksCollection.addTask(Task(id, name, TaskStatus::ON_HOLD, description));
	usersCollection[currentUserIndex]->addTaskId(id);

	id++;
}

void Session::getTask(unsigned taskId) const
{
	Vector<unsigned> tasksIds = usersCollection[currentUserIndex].getTasksIds();
	for (size_t i = 0; i < tasksIds.size(); i++)
	{
		if (tasksIds[i] == taskId)
		{
			tasksCollection.getTaskById(taskId)->print();
			return;
		}
	}

	std::cout << "There isn't any task with this id!" << std::endl;
}

void Session::getTask(MyString taskName) const
{
	Vector<unsigned> tasksIds = usersCollection[currentUserIndex].getTasksIds();
	for (size_t i = 0; i < tasksIds.size(); i++)
	{
		if (tasksCollection.getTaskById(tasksIds[i])->getName() == taskName)
		{
			tasksCollection.getTaskById(tasksIds[i])->print();
			return;
		}
	}

	std::cout << "There isn't any task with this name!" << std::endl;
}

void Session::listTasks(time_t dueDate) const
{
	Vector<unsigned> tasksIds = usersCollection[currentUserIndex].getTasksIds();

	for (size_t i = 0; i < tasksIds.size(); i++)
	{
		try
		{
			if (tasksCollection.getTaskById(tasksIds[i])->getDueDate() == dueDate)
				tasksCollection[tasksIds[i]].print();
		}
		catch (const std::exception& e)
		{

		}
	}
}

void Session::listAllTasks() const
{
	Vector<unsigned> tasksIds = usersCollection[currentUserIndex].getTasksIds();
	for (size_t i = 0; i < tasksIds.size(); i++)
	{
		if (tasksCollection.getTaskById(tasksIds[i]).isInitlized())
			tasksCollection.getTaskById(tasksIds[i])->print();
	}

	if (tasksIds.size() == 0)
		std::cout << "You still didn't add any tasks!" << std::endl;
}

void Session::listAllCompletedTasks() const
{
	Vector<unsigned> tasksIds = usersCollection[currentUserIndex].getTasksIds();

	bool isThereACompletedTask = false;
	for (size_t i = 0; i < tasksIds.size(); i++)
	{
		if (tasksCollection[tasksIds[i]].getStatus() == TaskStatus::DONE)
		{
			tasksCollection[tasksIds[i]].print();
			isThereACompletedTask = true;
		}
	}

	if (!isThereACompletedTask)
		std::cout << "You still didn't completed any tasks!" << std::endl;
}

void Session::listAllTasksFromDashboard() const
{
	if (usersCollection[currentUserIndex].getDashboardTasksIdsCount() == 0)
		std::cout << "You still didn't add any tasks to the dashboard!" << std::endl;

	usersCollection[currentUserIndex].printDashboard();
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

void Session::finishTask(unsigned taskId)
{
	if (usersCollection[currentUserIndex]->isOwnerOfTheTaskById(taskId))
	{
		tasksCollection.getTaskById(taskId)->setNewStatus(TaskStatus::DONE);
	}
	else
	{
		throw std::invalid_argument("Invalid task id!");
	}
}

void Session::deleteTask(unsigned taskId)
{
	if (usersCollection[currentUserIndex]->isOwnerOfTheTaskById(taskId))
	{
		for (size_t i = 0; i < tasksCollection.getTasksCount(); i++)
		{
			if (tasksCollection[i]->getId() == taskId)
			{
				usersCollection[currentUserIndex]->removeTaskFromDashboardById(taskId);
				tasksCollection.removeTaskByIndex(i);
				usersCollection[currentUserIndex]->removeTaskId(taskId);
				break;
			}
		}
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

void Session::addTaskToDashboardById(unsigned taskId)
{
	if (!usersCollection[currentUserIndex]->isOwnerOfTheTaskById(taskId))
		throw std::invalid_argument("Invalid task id!");

	if (tasksCollection.getTaskById(taskId)->getStatus() == TaskStatus::OVERDUE)
		throw std::invalid_argument("You cannot add this task to the dashboard because it's overdue!");

	usersCollection[currentUserIndex]->addTaskToDashboard(tasksCollection.getTaskById(taskId));
}

void Session::removeTaskFromDashboardById(unsigned taskId)
{
	if (!usersCollection[currentUserIndex]->isOwnerOfTheTaskById(taskId))
		throw std::invalid_argument("Invalid task id!");

	usersCollection[currentUserIndex]->removeTaskFromDashboardById(taskId);
}

void Session::addCollaboration(MyString collabName)
{
	for (size_t i = 0; i < collaborationsCollection.getCollaborationsCount(); i++)
	{
		if (collaborationsCollection[i]->getName() == collabName && collaborationsCollection[i]->getCreatorName() == usersCollection[currentUserIndex]->getUsername())
			throw std::invalid_argument("You have already created a collaboration with this name!");
	}

	collaborationsCollection.addCollaboration(Collaboration(collaborationsCollection.getMaxCollaborationId() + 1, collabName, usersCollection[currentUserIndex]->getUsername()));
}

void Session::deleteCollaboration(MyString collabName)
{

	if (!collaborationsCollection.getCollaborationByName(collabName).isInitlized())
		throw std::invalid_argument("There isn't a collaboration with this name!");

	for (size_t i = 0; i < collaborationsCollection.getCollaborationsCount(); i++)
	{
		if (collaborationsCollection[i]->getName() == collabName)
		{
			if (!collaborationsCollection[i]->isCreatorOfCollaboration(*usersCollection[currentUserIndex]))
				throw std::invalid_argument("Only the creator of the collaboration can delete it!");

			collaborationsCollection[i]->removeTasksForUsers(tasksCollection, usersCollection);
			collaborationsCollection.removeCollaborationByIndex(i);
		}
	}
}

void Session::listCollaborations() const
{
	bool isThereListedCollaborations = false;
	for (size_t i = 0; i < collaborationsCollection.getCollaborationsCount(); i++)
	{
		if (collaborationsCollection[i].isCreatorOfCollaboration(usersCollection[currentUserIndex])
			|| collaborationsCollection[i].isUserPartOfCollaboration(usersCollection[currentUserIndex]))
		{
			std::cout << collaborationsCollection[i].getName() << std::endl;
			isThereListedCollaborations = true;
		}
	}

	if (!isThereListedCollaborations)
		throw std::runtime_error("There aren't any collaborations that you craeted or you are a part of!");
}

void Session::addUserToCollaborationByUsername(MyString collabName, MyString username)
{
	for (size_t i = 0; i < usersCollection.getUsersCount(); i++)
	{
		if (usersCollection[i]->getUsername() == username)
		{
			try
			{
				if (!collaborationsCollection.getCollaborationByName(collabName).isInitlized())
					throw std::invalid_argument("There isn't a collaboration with this name!");

				if (collaborationsCollection.getCollaborationByName(collabName)->isUserPartOfCollaboration(*usersCollection[i]))
					throw std::invalid_argument("This user is already a part from the collaboration!");

				collaborationsCollection.getCollaborationByName(collabName)->addUser(*usersCollection[i]);
				std::cout << "User added successfully to " << collabName << "!" << std::endl;
				return;
			}
			catch (const std::invalid_argument& e)
			{
				std::cout << e.what() << std::endl;
				return;
			}
		}
	}

	throw std::invalid_argument("There isn't user with this name!");
}

void Session::listCollaboration(MyString collabName) const
{
	if (!collaborationsCollection.getCollaborationByName(collabName).isInitlized())
		throw std::invalid_argument("There isn't a collaboration with this name!");

	if (collaborationsCollection.getCollaborationByName(collabName)->isCreatorOfCollaboration(usersCollection[currentUserIndex])
		|| collaborationsCollection.getCollaborationByName(collabName)->isUserPartOfCollaboration(usersCollection[currentUserIndex]))
	{
		collaborationsCollection.getCollaborationByName(collabName)->printTasks(tasksCollection);
	}
	else
	{
		throw std::invalid_argument("You cannot list the tasks from this collaboration!");
	}
}

void Session::addCollaborationTask(MyString collabName, MyString username, MyString taskName, time_t taskDueDate, MyString taskDescription)
{
	if (!collaborationsCollection.getCollaborationByName(collabName).isInitlized())
		throw std::invalid_argument("There isn't a collaboration with this name!");

	if (!collaborationsCollection.getCollaborationByName(collabName)->isCreatorOfCollaboration(*usersCollection[currentUserIndex]))
		throw std::invalid_argument("You have to be the creator of the collaboration in order to assign tasks!");

	if (!collaborationsCollection.getCollaborationByName(collabName)->isUserPartOfCollaboration(usersCollection.getUserByUsername(username)))
		throw std::invalid_argument("You can only assign tasks to users which are in the collaboration!");

	if (collaborationsCollection.getCollaborationByName(collabName)->isTaskAlreadyInTheCollaboration(tasksCollection,username, taskName, taskDueDate, taskDescription))
		throw std::invalid_argument("This task is already assigned to the user!");

	SharedPtr<Task>* task = new SharedPtr<Task>(new CollaborationTask(id, taskName, taskDueDate, TaskStatus::ON_HOLD, taskDescription, username));
    tasksCollection.addTask(*task);
	collaborationsCollection.getCollaborationByName(collabName)->addCollaborationTaskById(id);

	for (size_t i = 0; i < usersCollection.getUsersCount(); i++)
	{
		if (usersCollection[i]->getUsername() == username)
		{
			usersCollection[i]->addTaskId(id);
			break;
		}
	}

	id++;
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
	collaborationsCollection.saveAllCollaborationsToFile(collaborationsFilename.c_str());
}