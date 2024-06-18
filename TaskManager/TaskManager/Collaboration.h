#pragma once
#include "UsersCollection.h";
#include "CollaborationTask.h";

class Collaboration 
{
public:
private:
	unsigned id;
	MyString name;
	const User& creator;
	UsersCollection users;

	Vector<CollaborationTask> tasks;
};