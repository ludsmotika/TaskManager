#pragma once
#include "User.h"
#include "Optional.hpp"

class CollaborationTask : public Task 
{
public:
	void print() const override;

    Task* clone() const override;
private:
	Optional<User> assignee;
};