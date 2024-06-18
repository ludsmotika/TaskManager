#pragma once
#include "Vector.hpp"
#include "Task.h"

class User 
{
private:
	MyString username;
	MyString password;

	Vector<unsigned> tasksIds;
public:
	User() = default;
	User(MyString username, MyString password);
	const MyString& getUsername() const;
	const MyString& getPassword() const;

	void setTasksIds(Vector<unsigned> ids) const;
};