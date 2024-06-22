#pragma once
#include "TasksCollection.h"
#include "WeakPtr.hpp"

class Dashboard
{
public:
	Dashboard();

	Dashboard(const Dashboard& other);
	Dashboard& operator=(const Dashboard& other);

	Dashboard(Dashboard&& other) noexcept;
	Dashboard& operator=(Dashboard&& other) noexcept;

	~Dashboard();

    void addTask(SharedPtr<Task> task);
	void addTask(const Task& task);

	void removeTaskById(unsigned taskId);

	size_t getTasksCount() const;

	const WeakPtr<Task>& operator[] (unsigned index) const;
private:
	WeakPtr<Task>* tasks;
	unsigned tasksCount;
	unsigned capacity;

	void free();
	void copyFrom(const Dashboard& other);
	void moveFrom(Dashboard&& other);
	void resize();
};

