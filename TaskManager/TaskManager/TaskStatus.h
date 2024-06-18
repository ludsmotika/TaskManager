#pragma once
#include <iostream>

enum class TaskStatus 
{
	ON_HOLD, 
	IN_PROCESS, 
	DONE, 
	OVERDUE
};

std::ostream& operator<<(std::ostream& os, TaskStatus status);