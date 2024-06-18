#pragma once
#include "TasksCollection.h"

class Dashboard
{
public:
	Dashboard() = default;
private:
	
	//Dashboard(User* user);

	User* user = nullptr;
	TasksCollection tasks;
};

