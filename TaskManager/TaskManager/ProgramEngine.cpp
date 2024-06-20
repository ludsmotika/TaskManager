//#include "ProgramEngine.h"
//#include "MyString.h"
//#include "GlobalFunctions.h"
//#include <iomanip>
//#include <ctime>
//#include <sstream>
//
//void ProgramEngine::run(Session& session)
//{
//	char currentRowInput[1024];
//	while (true)
//	{
//		std::cin.getline(currentRowInput, 1024);
//		MyString currentRow(currentRowInput);
//
//		int commandLength;
//		try
//		{
//			commandLength = getLengthToFirstCharOccurence(currentRow, ' ');
//		}
//		catch (const std::exception&)
//		{
//			commandLength = -1;
//		}
//
//		MyString currentCommand = commandLength == -1 ? currentRow : currentRow.substr(0, commandLength);
//
//		if (currentCommand == "register")
//		{
//			if (session.isThereALoggedInUser())
//			{
//				std::cout << "There is already a logged in user!" << std::endl;
//			}
//			else
//			{
//				try
//				{
//					int usernameLength = getLengthToFirstCharOccurence(currentRow.substr(commandLength + 1, currentRow.getSize() - commandLength - 1), ' ');
//					MyString username = currentRow.substr(commandLength + 1, usernameLength);
//					MyString password = currentRow.substr(commandLength + usernameLength + 2, currentRow.getSize() - (commandLength + usernameLength) - 2);
//
//					session.registerUser(username, password);
//					std::cout << "Registered successfully!" << std::endl;
//				}
//				catch (const std::invalid_argument& e)
//				{
//					std::cout << e.what() << std::endl;
//				}
//				catch (...)
//				{
//					std::cout << "Unexpected error occured!" << std::endl;
//				}
//			}
//		}
//		else if (currentCommand == "login")
//		{
//			if (session.isThereALoggedInUser())
//			{
//				std::cout << "There is already a logged in user!" << std::endl;
//			}
//			else
//			{
//				try
//				{
//					int usernameLength = getLengthToFirstCharOccurence(currentRow.substr(commandLength + 1, currentRow.getSize() - commandLength - 1), ' ');
//					MyString username = currentRow.substr(commandLength + 1, usernameLength);
//
//					MyString password = currentRow.substr(commandLength + usernameLength + 2, currentRow.getSize() - (commandLength + usernameLength) - 2);
//
//					session.loginUser(username, password);
//					std::cout << "Welcome back, " << username << "!" << std::endl;
//				}
//				catch (const std::invalid_argument& e)
//				{
//					std::cout << e.what() << std::endl;
//				}
//				catch (...)
//				{
//					std::cout << "Unexpected error occured!" << std::endl;
//				}
//			}
//		}
//		else if (currentCommand == "add-task")
//		{
//			if (!session.isThereALoggedInUser())
//			{
//				std::cout << "Login or register in order to add tasks!" << std::endl;
//			}
//			else
//			{
//				try
//				{
//					int taskNameLength = getLengthToFirstCharOccurence(currentRow.substr(commandLength + 1, currentRow.getSize() - commandLength - 1), ' ');
//					MyString taskName = currentRow.substr(commandLength + 1, taskNameLength);
//
//					int dueDateLength = getLengthToFirstCharOccurence(currentRow.substr(commandLength + taskNameLength + 2, currentRow.getSize() - commandLength - taskNameLength - 2), ' ');
//					MyString dueDate = currentRow.substr(commandLength + taskNameLength + 2, dueDateLength);
//
//					MyString description = currentRow.substr(commandLength + taskNameLength + dueDateLength + 3, currentRow.getSize() - (commandLength + taskNameLength + dueDateLength) - 3);
//
//					tm tm = {};
//					std::stringstream ss(dueDate.c_str());
//					ss >> std::get_time(&tm, "%Y-%m-%d");
//
//					session.addTask(taskName, mktime(&tm), description);
//				}
//				catch (const std::invalid_argument& e)
//				{
//					std::cout << e.what();
//				}
//				catch (...)
//				{
//					std::cout << "Unexpected error occured!" << std::endl;
//				}
//			}
//		}
//		else if (currentCommand == "update-task-name")
//		{
//		//update-task-name <id> <name>
//
//				if (!session.isThereALoggedInUser())
//				{
//					std::cout << "Login or register in order to add tasks!" << std::endl;
//				}
//				else
//				{
//					try
//					{
//						int taskNameLength = getLengthToFirstCharOccurence(currentRow.substr(commandLength + 1, currentRow.getSize() - commandLength - 1), ' ');
//						MyString taskName = currentRow.substr(commandLength + 1, taskNameLength);
//
//						int dueDateLength = getLengthToFirstCharOccurence(currentRow.substr(commandLength + taskNameLength + 2, currentRow.getSize() - commandLength - taskNameLength - 2), ' ');
//						MyString dueDate = currentRow.substr(commandLength + taskNameLength + 2, dueDateLength);
//
//						MyString description = currentRow.substr(commandLength + taskNameLength + dueDateLength + 3, currentRow.getSize() - (commandLength + taskNameLength + dueDateLength) - 3);
//
//						tm tm = {};
//						std::stringstream ss(dueDate.c_str());
//						ss >> std::get_time(&tm, "%Y-%m-%d");
//
//						session.addTask(taskName, mktime(&tm), description);
//					}
//					catch (const std::invalid_argument& e)
//					{
//						std::cout << e.what();
//					}
//					catch (...)
//					{
//						std::cout << "Unexpected error occured!" << std::endl;
//					}
//				}
//		}
//		else if (currentCommand == "start-task")
//		{
//
//		}
//		else if (currentCommand == "update-task-description")
//		{
//
//		}
//		else if (currentCommand == "remove-task-from-dashboard")
//		{
//
//		}
//		else if (currentCommand == "delete-task")
//		{
//
//		}
//		else if (currentCommand == "get-task")
//		{
//			//by id or by name
//		}
//		else if (currentCommand == "list-tasks")
//		{
//			//with or without date
//		}
//		else if (currentCommand == "list-completed-tasks")
//		{
//
//		}
//		else if (currentCommand == "list-dashboard")
//		{
//
//		}
//		else if (currentCommand == "finish-task")
//		{
//
//		}
//		else if (currentCommand == "logout")
//		{
//
//		}
//		else if (currentCommand == "exit")
//		{
//			break;
//		}
//	}
//
//	std::cout << "Exited successfully!";
//}



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
		std::stringstream currentRow(currentRowInput);

		MyString currentCommand;
		currentRow >> currentCommand;

		if (currentCommand == "register")
		{
			if (session.isThereALoggedInUser())
			{
				std::cout << "There is already a logged in user!" << std::endl;
			}
			else
			{
				try
				{
					MyString username;
					currentRow >> username;
					MyString password;
					currentRow >> password;

					session.registerUser(username, password);
					std::cout << "Registered successfully!" << std::endl;
				}
				catch (const std::invalid_argument& e)
				{
					std::cout << e.what() << std::endl;
				}
				catch (...)
				{
					std::cout << "Unexpected error occured!" << std::endl;
				}
			}
		}
		else if (currentCommand == "login")
		{
			if (session.isThereALoggedInUser())
			{
				std::cout << "There is already a logged in user!" << std::endl;
			}
			else
			{
				try
				{
					MyString username;
					currentRow >> username;
					MyString password;
					currentRow >> password;

					session.loginUser(username, password);
					std::cout << "Welcome back, " << username << "!" << std::endl;
				}
				catch (const std::invalid_argument& e)
				{
					std::cout << e.what() << std::endl;
				}
				catch (...)
				{
					std::cout << "Unexpected error occured!" << std::endl;
				}
			}
		}
		else if (currentCommand == "add-task")
		{
			if (!session.isThereALoggedInUser())
			{
				std::cout << "Login or register in order to add tasks!" << std::endl;
			}
			else
			{
				try
				{
					MyString taskName;
					currentRow >> taskName;

					MyString dueDate;
					currentRow >> dueDate;

					currentRow.ignore();
					size_t currentPos = currentRow.tellg();
					currentRow.seekg(0, std::ios::end);
					size_t endPos = currentRow.tellg();
					size_t remainingSymbolsCount = endPos - currentPos;
					currentRow.seekg(currentPos);

					char* remainder = new char[remainingSymbolsCount];
					currentRow.read(remainder, remainingSymbolsCount);

					MyString description(remainder);
					description = description.substr(0, remainingSymbolsCount);

					tm tm = {};
					std::stringstream ss(dueDate.c_str());
					ss >> std::get_time(&tm, "%Y-%m-%d");

					session.addTask(taskName, mktime(&tm), description);

					delete[] remainder;
				}
				catch (const std::invalid_argument& e)
				{
					std::cout << e.what();
				}
				catch (...)
				{
					std::cout << "Unexpected error occured!" << std::endl;
				}
			}
		}
		else if (currentCommand == "update-task-name")
		{
			if (!session.isThereALoggedInUser())
			{
				std::cout << "Login or register in order to modify tasks!" << std::endl;
			}
			else
			{
				try
				{
					unsigned taskId;
					currentRow >> taskId;

					MyString newName;
					currentRow >> newName;

					session.updateTaskName(taskId, newName);

					std::cout << "Task name updated successfully!";
				}
				catch (const std::invalid_argument& e)
				{
					std::cout << e.what();
				}
				catch (...)
				{
					std::cout << "Unexpected error occured!" << std::endl;
				}
			}
		}
		else if (currentCommand == "start-task")
		{
			if (!session.isThereALoggedInUser())
			{
				std::cout << "Login or register in order to modify tasks!" << std::endl;
			}
			else
			{
				try
				{
					unsigned taskId;
					currentRow >> taskId;

					session.startTaskById(taskId);

					std::cout << "Task started successfully!";
				}
				catch (const std::invalid_argument& e)
				{
					std::cout << e.what();
				}
				catch (...)
				{
					std::cout << "Unexpected error occured!" << std::endl;
				}
			}
		}
		else if (currentCommand == "update-task-description")
		{
			//update-task-description <id> <description>
			if (!session.isThereALoggedInUser())
			{
				std::cout << "Login or register in order to add tasks!" << std::endl;
			}
			else
			{
				try
				{
					unsigned taskId;
					currentRow >> taskId;

					currentRow.ignore();
					size_t currentPos = currentRow.tellg();
					currentRow.seekg(0, std::ios::end);
					size_t endPos = currentRow.tellg();
					size_t remainingSymbolsCount = endPos - currentPos;
					currentRow.seekg(currentPos);

					char* remainder = new char[remainingSymbolsCount];
					currentRow.read(remainder, remainingSymbolsCount);

					MyString newDescription(remainder);
					newDescription = newDescription.substr(0, remainingSymbolsCount);

					session.updateTaskDescription(taskId, newDescription);
				}
				catch (const std::invalid_argument& e)
				{
					std::cout << e.what();
				}
				catch (...)
				{
					std::cout << "Unexpected error occured!" << std::endl;
				}
			}

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
			if (!session.isThereALoggedInUser())
			{
				std::cout << "There isn't a logged in user!" << std::endl;
			}
			else 
			{
				session.logout();
				std::cout << "Logged out successfully!" << std::endl;
			}
		}
		else if (currentCommand == "exit")
		{
			session.closeSession();
			break;
		}
	}

	std::cout << "Exited successfully!";
}