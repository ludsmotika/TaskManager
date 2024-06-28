#pragma once
#include "Session.h"

class ProgramEngine 
{
public:
	static void run(Session& session);
private:
	static void handleRegister(std::stringstream& currentRow, Session& session);
	static void handleLogin(std::stringstream& currentRow, Session& session);
	static void handleAddTask(std::stringstream& currentRow, Session& session);
	static void handleUpdateTaskName(std::stringstream& currentRow, Session& session);
	static void handleUpdateTaskDescription(std::stringstream& currentRow, Session& session);
	static void handleStartTask(std::stringstream& currentRow, Session& session);
	static void handleRemoveTaskFromDashboard(std::stringstream& currentRow, Session& session);
	static void handleDeleteTask(std::stringstream& currentRow, Session& session);
	static void handleGetTask(std::stringstream& currentRow, Session& session);
	static void handleListTasks(std::stringstream& currentRow, Session& session);
	static void handleAddTaskToDashboard(std::stringstream& currentRow, Session& session);
	static void handleFinishTask(std::stringstream& currentRow, Session& session);
	static void handleAddCollaboration(std::stringstream& currentRow, Session& session);
	static void handleDeleteCollaboration(std::stringstream& currentRow, Session& session);
	static void handleListCollaborations(Session& session);
	static void handleAddUser(std::stringstream& currentRow, Session& session);
	static void handleAssignTask(std::stringstream& currentRow, Session& session);
	
};