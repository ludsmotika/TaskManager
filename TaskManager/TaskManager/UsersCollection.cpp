#include "UsersCollection.h"
#include "TasksCollection.h"
#include "GlobalFunctions.h"
#include <fstream>

// format in which we will save the users in the file is 
// username
// password

UsersCollection::UsersCollection()
{
	//fill the collection
}

void UsersCollection::readUsersFromFile(const char* filename, TasksCollection& tasks)
{
	if (!filename)
		throw std::invalid_argument("NullPtr passed as a parameter");

	std::ifstream is(filename, std::ios::binary);

	if (!is.is_open())
		throw std::invalid_argument("Cannot open file for writing!");

	while (true)
	{
		unsigned usernameLength;
		is.read((char*)&usernameLength, sizeof(unsigned));

		char* username = new char[usernameLength];
		is.read(username, sizeof(char) * usernameLength);

		unsigned passwordLength;
		is.read((char*)&passwordLength, sizeof(unsigned));

		char* password = new char[passwordLength];
		is.read(password, sizeof(char) * passwordLength);

		if (is.eof()) break;

		MyString parsedUsername(username);
		MyString parsedPassword(password);

		User* user = new User(parsedUsername.substr(0, usernameLength), parsedPassword.substr(0, passwordLength));

		unsigned tasksIdsCount;
		is.read((char*)&tasksIdsCount, sizeof(unsigned));

		for (size_t i = 0; i < tasksIdsCount; i++)
		{
			unsigned currentTaskId;
			is.read((char*)&currentTaskId, sizeof(unsigned));
			user->addTaskId(currentTaskId);
		}

		unsigned dashboardTasksIdsCount;
		is.read((char*)&dashboardTasksIdsCount, sizeof(unsigned));

		for (size_t i = 0; i < dashboardTasksIdsCount; i++)
		{
			unsigned currentDashboardTaskId;
			is.read((char*)&currentDashboardTaskId, sizeof(unsigned));
			user->addTaskToDashboard(tasks.getTaskById(currentDashboardTaskId));
		}

		addUser(*user);

		delete[] username;
		delete[] password;
	}
}

void UsersCollection::saveUserToFile(std::ofstream& os, const User& user)
{
	unsigned nameLen = user.getUsername().getSize();

	os.write((const char*)&nameLen, sizeof(unsigned));
	os.write(user.getUsername().c_str(), sizeof(char) * user.getUsername().getSize());

	unsigned passLen = user.getPassword().getSize();

	os.write((const char*)&passLen, sizeof(unsigned));
	os.write(user.getPassword().c_str(), sizeof(char) * user.getPassword().getSize());

	unsigned idsCount = user.getTasksIds().size();

	os.write((const char*)&idsCount, sizeof(unsigned));
	os.write((const char*)&user.getTasksIds()[0], sizeof(unsigned) * user.getTasksIds().size());

	unsigned dashboardTaskIdsCount = user.getDashboard().getTasksCount();

	os.write((const char*)&dashboardTaskIdsCount, sizeof(unsigned));
	for (size_t i = 0; i < dashboardTaskIdsCount; i++)
		os.write((const char*)user.getDashboard()[i].lock()->getId(), sizeof(unsigned));
}

size_t UsersCollection::getUsersCount() const
{
	return users.size();
}

User* UsersCollection::operator[] (unsigned index)
{
	return &users[index];
}

const User& UsersCollection::operator[] (unsigned index) const
{
	return users[index];
}

void UsersCollection::addUser(const User& user)
{
	this->users.push_back(user);
}

void UsersCollection::saveAllUserToFile(const char* filename) const
{
	if (!filename)
		throw std::invalid_argument("NullPtr passed as a parameter!");

	std::ofstream os(filename, std::ios::binary);

	if (!os.is_open())
		throw std::invalid_argument("Cannot open file for reading!");

	for (size_t i = 0; i < getUsersCount(); i++)
		UsersCollection::saveUserToFile(os, users[i]);
}
