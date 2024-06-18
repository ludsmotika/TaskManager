#include "Task.h"
#include "MyString.h"

Task::Task(unsigned id, MyString name, time_t dueDate, TaskStatus status, MyString description): id(id),name(name),dueDate(dueDate),status(status), description(description)
{
	
}

void Task::print() const 
{
	std::cout << "Task name: " << getName()<< std::endl;
	std::cout << "Task ID: " << getId() << std::endl;
	std::cout << "Due date: " << getDueDate() << std::endl;
	std::cout << "Status: " << getStatus() << std::endl;
	std::cout << "Task desc: " << getDescription()<< std::endl;
}

Task* Task::clone() const
{
	Task* newObj = new  (std::nothrow)Task(*this);
	return newObj;
}

unsigned Task::getId() const 
{
	return this->id;
}

TaskStatus Task::getStatus() const 
{
	return this->status;
}

time_t Task::getDueDate() const 
{
	return this->dueDate;
}

MyString Task::getName() const 
{
	return this->name;
}

MyString Task::getDescription() const 
{
	return this->description;
}