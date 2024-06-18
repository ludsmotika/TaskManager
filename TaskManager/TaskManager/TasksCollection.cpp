#include "TasksCollection.h"
#include "GlobalFunctions.h"

//TODO see if this constructor will work right after thinking about how to save the tasks

TasksCollection::TasksCollection()
{
	capacity = 8;
	tasksCount = 0;
	tasks = new Task * [capacity];

	//fill the collection
}

TasksCollection::TasksCollection(const TasksCollection& other)
{
	copyFrom(other);
}

TasksCollection& TasksCollection::operator=(const TasksCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

TasksCollection::TasksCollection(TasksCollection&& other) noexcept
{
	moveFrom(std::move(other));
}

TasksCollection& TasksCollection::operator=(TasksCollection&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

TasksCollection::~TasksCollection()
{
	free();
}

void TasksCollection::readTasksFromFile(const char* filename)
{

}


void TasksCollection::addTask(const Task& task)
{
	if (tasksCount == capacity)
		resize();
	tasks[tasksCount++] = task.clone();
}

size_t TasksCollection::getTasksCount() const
{
	return tasksCount;
}

const Task& TasksCollection::operator[] (unsigned index) const
{
	return *tasks[index];
}

Task* TasksCollection::operator[] (unsigned index)
{
	return tasks[index];
}

void TasksCollection::free()
{
	for (size_t i = 0; i < tasksCount; i++)
		delete tasks[i];
	delete[] tasks;
}

void TasksCollection::copyFrom(const TasksCollection& other)
{
	tasks = new Task * [other.capacity];
	tasksCount = other.tasksCount;
	capacity = other.capacity;

	for (size_t i = 0; i < tasksCount; i++)
	{
		Task* cloned = other.tasks[i]->clone();
		if (cloned)
			tasks[i] = cloned;
	}
}

void TasksCollection::moveFrom(TasksCollection&& other)
{
	tasksCount = other.tasksCount;
	capacity = other.capacity;

	tasks = other.tasks;
	other.tasks = nullptr;

	other.tasksCount = other.capacity = 0;
}

void TasksCollection::resize()
{
	Task** newCollection = new Task* [capacity *= 2];
	for (size_t i = 0; i < tasksCount; i++)
		newCollection[i] = tasks[i];
	delete[] tasks;
	tasks = newCollection;
}