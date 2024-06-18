#include "Session.h"

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

		usersCollection.readUsersFromFile(usersFilename);
		tasksCollection.readTasksFromFile(tasksFilename);
		//dashboard(user,tasks);
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
	currentUserIndex = usersCollection.getUsersCount()-1;

	saveUserToFile(currentUser);

	this->currentUserIndex = usersCollection.getUsersCount() - 1;
}

void Session::saveUserToFile(const User& user) const
{
	//open the file
	//write binary in thw format
	//<username length> username
	//<password length> password
	//<TasksIdsCount> id1 id2 id3 ...


}

void Session::loginUser(MyString username, MyString password)
{
	for (size_t i = 0; i < usersCollection.getUsersCount(); i++)
	{
		if (usersCollection[i]->getUsername() == username)
			this->currentUserIndex = i;
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

	//TODO: generate the id to not be the tasksCount
	tasksCollection.addTask(Task(tasksCollection.getTasksCount(), name, dueDate, TaskStatus::ON_HOLD, description));
}


