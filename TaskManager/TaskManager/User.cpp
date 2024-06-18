#include "User.h"

User::User(MyString username, MyString password) :username(username),password(password) {}

const MyString& User::getUsername() const
{
	return this->username;
}

const MyString& User::getPassword() const
{
	return this->password;
}