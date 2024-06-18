#include "CollaborationTask.h"

void CollaborationTask::print() const 
{
	std::cout << "colab task";
}

Task* CollaborationTask::clone() const 
{
	Task* newObj = new  (std::nothrow)CollaborationTask(*this);
	return newObj;
}

