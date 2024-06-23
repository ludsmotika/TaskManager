#pragma once
#include "User.h"
#include "Optional.hpp"

class CollaborationTask : public Task 
{
public:
	CollaborationTask(unsigned id, MyString name, time_t dueDate, TaskStatus status, MyString description, MyString assignee);

	MyString getAssignee() const;
	void print() const override;
    Task* clone() const override;
private:
	MyString assignee;
};