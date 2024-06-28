#include "TasksCollection.h"
#include "GlobalFunctions.h"
#include "CollaborationTask.h"
#include <fstream>
#include <iostream>
#include <typeinfo>
#pragma warning (disable : 4996)

TasksCollection::TasksCollection()
{
	capacity = 8;
	tasksCount = 0;
	tasks = new SharedPtr<Task>[capacity];
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
	if (!filename)
		throw std::invalid_argument("Nullptr passed as an argument");

	std::ifstream is(filename, std::ios::binary | std::ios::in);

	if (!is.is_open())
		throw std::invalid_argument("Cannot open file for reading!");

	while (true)
	{
		unsigned id;
		is.read((char*)&id, sizeof(unsigned));

		size_t taskNameLength;
		is.read((char*)&taskNameLength, sizeof(size_t));

		char* taskName = new char[taskNameLength];
		is.read(taskName, sizeof(char) * taskNameLength);

		bool isThereADueDate = false;
		is.read((char*)&isThereADueDate, sizeof(bool));

		time_t dueDate = {};

		if (isThereADueDate)
			is.read((char*)&dueDate, sizeof(time_t));

		TaskStatus status;
		is.read((char*)&status, sizeof(TaskStatus));

		size_t taskDescriptionLength;
		is.read((char*)&taskDescriptionLength, sizeof(size_t));

		char* description = new char[taskDescriptionLength];
		is.read(description, sizeof(char) * taskDescriptionLength);

		bool isItACollabTask = false;
		is.read((char*)&isItACollabTask, sizeof(bool));

		MyString parsedTaskName(taskName);
		MyString parsedTaskDescription(description);

		if (is.eof()) break;

		if (isItACollabTask)
		{
			size_t collabTaskAssigneeLength;
			is.read((char*)&collabTaskAssigneeLength, sizeof(size_t));

			char* assigneeName = new char[collabTaskAssigneeLength];
			is.read(assigneeName, sizeof(char) * collabTaskAssigneeLength);

			MyString parsedAssigneeName(assigneeName);

			time_t now = time(nullptr);
			tm* localTime = localtime(&now);
			localTime->tm_hour = 0;
			localTime->tm_min = 0;
			localTime->tm_sec = 0;
			time_t currentTime = mktime(localTime);

			if (dueDate < currentTime)
				status = TaskStatus::OVERDUE;

			addTask(new CollaborationTask(id,parsedTaskName.substr(0, taskNameLength), dueDate, status, parsedTaskDescription.substr(0, taskDescriptionLength), parsedAssigneeName.substr(0, collabTaskAssigneeLength)));

		}
		else if(isThereADueDate)
		{

			time_t now = time(nullptr);
			tm* localTime = localtime(&now);
			localTime->tm_hour = 0;
			localTime->tm_min = 0;
			localTime->tm_sec = 0;
			time_t currentTime = mktime(localTime);

			if (dueDate < currentTime)
				status = TaskStatus::OVERDUE;

			addTask(new Task(id,parsedTaskName.substr(0, taskNameLength), dueDate, status, parsedTaskDescription.substr(0, taskDescriptionLength)));
		}
		else
		{
			addTask(new Task(id, parsedTaskName.substr(0, taskNameLength), status, parsedTaskDescription.substr(0, taskDescriptionLength)));
		}

		delete[] taskName;
		delete[] description;
	}
}

void TasksCollection::addTask(const Task& task)
{
	addTask(task.clone());
}

size_t TasksCollection::getTasksCount() const
{
	return tasksCount;
}

const Task& TasksCollection::operator[] (unsigned index) const
{
	return *tasks[index];
}

SharedPtr<Task> TasksCollection::operator[] (unsigned index)
{
	return tasks[index];
}

void TasksCollection::free()
{
	delete[] tasks;
}

void TasksCollection::copyFrom(const TasksCollection& other)
{
	tasks = new SharedPtr<Task>[other.capacity];
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
	SharedPtr<Task>* newCollection = new SharedPtr<Task>[capacity *= 2];
	for (size_t i = 0; i < tasksCount; i++)
		newCollection[i] = tasks[i];
	delete[] tasks;
	tasks = newCollection;
}

SharedPtr<Task> TasksCollection::getTaskById(unsigned id) const
{
	for (size_t i = 0; i < tasksCount; i++)
	{
		if (tasks[i]->getId() == id)
			return tasks[i];
	}

	return nullptr;
}

void TasksCollection::saveAllTasksToFile(const char* filename)
{
	if (!filename)
		throw std::invalid_argument("Nullptr passed as a parameter!");

	std::ofstream os(filename, std::ios::out | std::ios::binary);

	if (!os.is_open())
		throw std::invalid_argument("Cannot open file for reading!");

	for (size_t i = 0; i < tasksCount; i++)
		saveTaskToFile(os, *tasks[i]);
}

void TasksCollection::addTask(const SharedPtr<Task>& task)
{
	if (tasksCount == capacity)
		resize();
	tasks[tasksCount++] = task;
}

void TasksCollection::removeTaskByIndex(unsigned index)
{
	if (index >= 0 && index < tasksCount)
		std::swap(tasks[index], tasks[tasksCount - 1]);

	tasks[tasksCount-1] = nullptr;
	tasksCount--;
}

unsigned TasksCollection::getMaxTaskId() const
{
	unsigned biggestId = 0;

	for (size_t i = 0; i < tasksCount; i++)
	{
		if (tasks[i].isInitlized() && tasks[i]->getId() > biggestId)
			biggestId = tasks[i]->getId();
	}
	return biggestId;
}

void TasksCollection::saveTaskToFile(std::ofstream& os, Task& task)
{
	unsigned taskId = task.getId();
	os.write((const char*)&taskId, sizeof(unsigned));

	size_t taskNameLength = task.getName().getSize();
	os.write((const char*)&taskNameLength, sizeof(size_t));
	os.write(task.getName().c_str(), sizeof(char) * task.getName().getSize());


	bool isThereADueDateForCurrentTask = true;

	try
	{
		time_t time = task.getDueDate();
		os.write((const char*)&isThereADueDateForCurrentTask, sizeof(bool));
		os.write((const char*)&time, sizeof(time_t));
	}
	catch (const std::runtime_error& e)
	{
		isThereADueDateForCurrentTask = false;
		os.write((const char*)&isThereADueDateForCurrentTask, sizeof(bool));
	}

	TaskStatus status = task.getStatus();
	os.write((const char*)&status, sizeof(TaskStatus));

	size_t taskDescriptionLength = task.getDescription().getSize();
	os.write((const char*)&taskDescriptionLength, sizeof(size_t));
	os.write(task.getDescription().c_str(), sizeof(char) * task.getDescription().getSize());


	bool isItCollabTask = false;
	if (CollaborationTask* collabTask = dynamic_cast<CollaborationTask*>(&task))
	{
		isItCollabTask = true;
		os.write((const char*)&isItCollabTask, sizeof(bool));

		size_t collabTaskAssigneeLength = collabTask->getAssignee().getSize();
		os.write((const char*)&collabTaskAssigneeLength, sizeof(size_t));
		os.write(collabTask->getAssignee().c_str(), sizeof(char) * collabTaskAssigneeLength);
	}
	else
	{
		os.write((const char*)&isItCollabTask, sizeof(bool));
	}

}
