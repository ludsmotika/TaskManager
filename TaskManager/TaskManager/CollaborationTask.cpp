#include "CollaborationTask.h"
#include "GlobalFunctions.h"


CollaborationTask::CollaborationTask(unsigned id, MyString name, time_t dueDate, TaskStatus status, MyString description, MyString assignee) :Task(id, name, dueDate, status, description), assignee(assignee) 
{

}

void CollaborationTask::print() const 
{
	std::cout << "Task from collaboration" << std::endl;
	std::cout << "Task name: " << getName() << std::endl;
	std::cout << "Task ID: " << getId() << std::endl;
	try
	{
		std::cout << "Due date: ";
		printTime(getDueDate());
		std::cout << std::endl;
	}
	catch (const std::runtime_error& e)
	{
		std::cout << "-" << std::endl;
	}
	std::cout << "Status: " << getStatus() << std::endl;
	std::cout << "Task desc: " << getDescription() << std::endl;
	std::cout << std::endl;
}

Task* CollaborationTask::clone() const 
{
	Task* newObj = new  (std::nothrow)CollaborationTask(*this);
	return newObj;
}

