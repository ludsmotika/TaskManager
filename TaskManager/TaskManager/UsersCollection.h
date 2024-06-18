#pragma once
#include "User.h"

class UsersCollection 
{
public:
	UsersCollection();

	void readUsersFromFile(const char* filename);

	size_t getUsersCount() const;

	const User& operator[] (unsigned index) const;
	User* operator[] (unsigned index);

	void addUser(const User& user);

private:
	Vector<User> users;
};