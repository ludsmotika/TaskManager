#include "UsersCollection.h"
#include "GlobalFunctions.h"

// format in which we will save the users in the file is 
// username
// password

UsersCollection::UsersCollection()
{
	//fill the collection
}

void UsersCollection::readUsersFromFile(const char* filename)
{

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
