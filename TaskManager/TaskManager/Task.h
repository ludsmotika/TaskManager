#pragma once
#include "MyString.h"
#include "TaskStatus.h"
#include <ctime>

class Task 
{
public:

	//TODO: does the task has to create the id or it should be passed to the constructor
	Task(unsigned id,MyString name, time_t dueDate, TaskStatus status, MyString description);
	virtual ~Task() = default;

	virtual Task* clone()  const;

	virtual void print() const;
	unsigned getId() const;
	TaskStatus getStatus() const;
	time_t getDueDate() const;
	MyString getName() const;
	MyString getDescription() const;

private:
	unsigned id;
	MyString name;
	time_t dueDate;
	TaskStatus status;
	MyString description;
};