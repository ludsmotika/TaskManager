#include "Dashboard.h"

Dashboard::Dashboard()
{
	capacity = 8;
	tasksCount = 0;
	tasks = new WeakPtr<Task>[capacity];
}

Dashboard::Dashboard(const Dashboard& other)
{
	copyFrom(other);
}

Dashboard& Dashboard::operator=(const Dashboard& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Dashboard::Dashboard(Dashboard&& other) noexcept
{
	moveFrom(std::move(other));
}

Dashboard& Dashboard::operator=(Dashboard&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Dashboard::~Dashboard()
{
	free();
}


void Dashboard::addTask(SharedPtr<Task> task)
{
	if (tasksCount == capacity)
		resize();
	tasks[tasksCount++] = WeakPtr<Task>(task);
}

void Dashboard::addTask(const Task& task)
{
	addTask(task.clone());
}

size_t Dashboard::getTasksCount() const
{
	return tasksCount;
}

const WeakPtr<Task>& Dashboard::operator[] (unsigned index) const
{
	return tasks[index];
}

void Dashboard::free()
{
	delete[] tasks;
}

void Dashboard::copyFrom(const Dashboard& other)
{
	tasks = new WeakPtr<Task>[other.capacity];
	tasksCount = other.tasksCount;
	capacity = other.capacity;

	for (size_t i = 0; i < tasksCount; i++)
		tasks[i] = other.tasks[i];
}

void Dashboard::moveFrom(Dashboard&& other)
{
	tasksCount = other.tasksCount;
	capacity = other.capacity;

	tasks = other.tasks;
	other.tasks = nullptr;

	other.tasksCount = other.capacity = 0;
}

void Dashboard::resize()
{
	WeakPtr<Task>* newCollection = new WeakPtr<Task>[capacity *= 2];
	for (size_t i = 0; i < tasksCount; i++)
		newCollection[i] = tasks[i];
	delete[] tasks;
	tasks = newCollection;
}


void Dashboard::removeTaskById(unsigned taskId)
{
	for (size_t i = 0; i < tasksCount; i++)
	{
		if (!tasks[i].expired())
		{
			if (tasks[i].lock()->getId() == taskId)
			{
				std::swap(tasks[i], tasks[tasksCount - 1]);
				tasks[tasksCount - 1].~WeakPtr();
				tasksCount--;
				break;
			}
		}
	}

}
