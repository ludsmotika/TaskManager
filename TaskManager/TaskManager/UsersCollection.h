#pragma once
#include "User.h"

class UsersCollection 
{
public:
	UsersCollection();

	void readUsersFromFile(const char* filename, TasksCollection& tasks);

	size_t getUsersCount() const;

	const User& operator[] (unsigned index) const;
	User* operator[] (unsigned index);

	void addUser(const User& user);

	static void saveUserToFile(std::ofstream& os,const User& user);
	
	void saveAllUserToFile(const char* filename) const;
private:
	Vector<User> users;
};