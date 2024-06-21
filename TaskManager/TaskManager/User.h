#pragma once
#include "Vector.hpp"
#include "Task.h"
#include "Dashboard.h"

class User 
{
private:
	MyString username;
	MyString password;

	Dashboard dashboard;

	Vector<unsigned> tasksIds;

public:
	User() = default;
	User(MyString username, MyString password);
	const MyString& getUsername() const;
	const MyString& getPassword() const;
	const Dashboard& getDashboard() const;
	const Vector<unsigned>& getTasksIds() const;
	unsigned getDashboardTasksIdsCount() const;

	void removeTaskId(unsigned taskId);

	void addTaskId(unsigned id);
	void addTaskToDashboard(SharedPtr<Task> task);
	bool isOwnerOfTheTaskById(unsigned taskId);

	void setTasksIds(const Vector<unsigned>& ids);
};