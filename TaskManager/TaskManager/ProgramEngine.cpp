#include "ProgramEngine.h"
#include "MyString.h"
#include "GlobalFunctions.h"
#include <iomanip>
#include <ctime>
#include <sstream>

void ProgramEngine::run(Session& session)
{
	char currentRowInput[1024];
	while (true)
	{
		std::cin.getline(currentRowInput, 1024);
		MyString currentRow(currentRowInput);

		int commandLength;
		try
		{
			commandLength = getLengthToFirstCharOccurence(currentRow, ' ');
		}
		catch (const std::exception&)
		{
			commandLength = -1;
		}

		MyString currentCommand = commandLength == -1 ? currentRow : currentRow.substr(0, commandLength);

		if (currentCommand == "register")
		{
			int usernameLength = getLengthToFirstCharOccurence(currentRow.substr(commandLength + 1, currentRow.getSize() - commandLength - 1), ' ');
			MyString username = currentRow.substr(commandLength+1, usernameLength);

			MyString password = currentRow.substr(commandLength + usernameLength+ 2, currentRow.getSize() - (commandLength + usernameLength) -2);
			session.registerUser(username, password);
		}
		else if (currentCommand == "login")
		{
			int usernameLength = getLengthToFirstCharOccurence(currentRow.substr(commandLength, currentRow.getSize() - commandLength), ' ');
			MyString username = currentRow.substr(commandLength, usernameLength);

			MyString password = currentRow.substr(commandLength + usernameLength, currentRow.getSize() - (commandLength + usernameLength));
			session.loginUser(username, password);
		}
		else if (currentCommand == "add-task")
		{
			int taskNameLength = getLengthToFirstCharOccurence(currentRow.substr(commandLength, currentRow.getSize() - commandLength), ' ');
			MyString taskName = currentRow.substr(commandLength, taskNameLength);

			int dueDateLength = getLengthToFirstCharOccurence(currentRow.substr(commandLength + taskNameLength, currentRow.getSize() - commandLength - taskNameLength), ' ');
			MyString dueDate = currentRow.substr(commandLength + taskNameLength, dueDateLength);

			MyString description = currentRow.substr(commandLength + taskNameLength + dueDateLength, currentRow.getSize() - (commandLength + taskNameLength + dueDateLength));

			tm tm = {};
			std::stringstream ss(dueDate.c_str());
			ss >> std::get_time(&tm, "%Y-%m-%d");

			session.addTask(taskName, mktime(&tm), description);
		}
		else if (currentCommand == "update-task-name")
		{

		}
		else if (currentCommand == "start-task")
		{

		}
		else if (currentCommand == "update-task-description")
		{

		}
		else if (currentCommand == "remove-task-from-dashboard")
		{

		}
		else if (currentCommand == "delete-task")
		{

		}
		else if (currentCommand == "get-task")
		{
			//by id or by name
		}
		else if (currentCommand == "list-tasks")
		{
			//with or without date
		}
		else if (currentCommand == "list-completed-tasks")
		{

		}
		else if (currentCommand == "list-dashboard")
		{

		}
		else if (currentCommand == "finish-task")
		{

		}
		else if (currentCommand == "logout")
		{

		}
		else if (currentCommand == "exit")
		{
			break;
		}
	}

	std::cout << "Exited successfully!";
}