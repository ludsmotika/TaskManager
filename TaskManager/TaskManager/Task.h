#pragma once
#include "MyString.h"
#include "TaskStatus.h"
#include "Optional.hpp"
#include <ctime>

class Task 
{
public:

	//TODO: does the task has to create the id or it should be passed to the constructor
	Task(unsigned id,MyString name, time_t dueDate, TaskStatus status, MyString description);
	Task(unsigned id, MyString name, TaskStatus status, MyString description);

	virtual ~Task() = default;

	virtual Task* clone()  const;

	virtual void print() const;	
	unsigned getId() const;
	TaskStatus getStatus() const;
	time_t getDueDate() const;
	MyString getName() const;
	MyString getDescription() const;

	void setNewName(MyString name);
	void setNewStatus(TaskStatus status);
	void setNewDescription(MyString description);
private:
	unsigned id;
	MyString name;
	Optional<time_t> dueDate;
	TaskStatus status;
	MyString description;
};