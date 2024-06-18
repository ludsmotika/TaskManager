#pragma once
#include "Task.h"

class TasksCollection
{
public:
	TasksCollection();

	TasksCollection(const TasksCollection& other);
	TasksCollection& operator=(const TasksCollection& other);

	TasksCollection(TasksCollection&& other) noexcept;
	TasksCollection& operator=(TasksCollection&& other) noexcept;

	~TasksCollection();

	void readTasksFromFile(const char* filename);

	void addTask(const Task& task);

	size_t getTasksCount() const;

	const Task& operator[] (unsigned index) const;
	Task* operator[] (unsigned index);

private:
	Task** tasks;
	size_t tasksCount;
	size_t capacity;

	void free();
	void copyFrom(const TasksCollection& other);
	void moveFrom(TasksCollection&& other);
	void resize();
};