#pragma once
#include "Task.h"
#include "SharedPtr.hpp"

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

	void addTask(Task* task);
	void addTask(const Task& task);

	size_t getTasksCount() const;

	SharedPtr<Task> getTaskById(unsigned id) const;
	unsigned getMaxTaskId() const;

	const Task& operator[] (unsigned index) const;
	SharedPtr<Task> operator[] (unsigned index);

	void removeTaskByIndex(unsigned index);

	void saveAllTasksToFile(const char* filename);
private:
	SharedPtr<Task>* tasks;
	size_t tasksCount;
	size_t capacity;

	void free();
	void copyFrom(const TasksCollection& other);
	void moveFrom(TasksCollection&& other);
	void resize();

	void saveTaskToFile(std::ofstream& os, const Task& task);
};
