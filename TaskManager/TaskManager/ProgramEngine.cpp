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
					bool isDueDateValid = isValidDate(dueDate);

					tm tm = {};
					if (isDueDateValid)
					{
						time_t now = time(0);
						std::stringstream ss(dueDate.c_str());
						ss >> std::get_time(&tm, "%Y-%m-%d");
						currentRow.ignore();

						if (mktime(&tm) < now)
						{
							throw std::invalid_argument("Cannot add task with date which has already passed!");
							isDueDateValid = false;
						}
					}

					size_t currentPos = currentRow.tellg();
					currentRow.seekg(0, std::ios::end);
					size_t endPos = currentRow.tellg();
					size_t remainingSymbolsCount = endPos - currentPos;
					currentRow.seekg(currentPos);

					char* remainder = new char[remainingSymbolsCount];
					currentRow.read(remainder, remainingSymbolsCount);

					MyString description(remainder);
					description = description.substr(0, remainingSymbolsCount);

					if (isValidDate(dueDate))
					{
						session.addTask(taskName, mktime(&tm), description);
					}
					else
					{
						MyString wholeDescription = dueDate + description;
						session.addTask(taskName, wholeDescription);
					}

					std::cout << "Task added successfully!" << std::endl;

					delete[] remainder;
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

					std::cout << "Task name updated successfully!" << std::endl;
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

					std::cout << "Task started successfully!" << std::endl;
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
		else if (currentCommand == "update-task-description")
		{
			if (!session.isThereALoggedInUser())
			{
				std::cout << "Login or register in order to update tasks!" << std::endl;
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
					std::cout << e.what() << std::endl;
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

					session.deleteTask(taskId);

					std::cout << "Task deleted successfully!" << std::endl;
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
		else if (currentCommand == "get-task")
		{
			if (!session.isThereALoggedInUser())
			{
				std::cout << "Login or register in order to get tasks!" << std::endl;
			}
			else
			{
				try
				{
					unsigned taskId = 0;
					currentRow >> taskId;
					if (currentRow.fail())
						throw std::runtime_error("Invalid id!");

					session.getTask(taskId);
				}
				catch (const std::exception& e)
				{
					currentRow.clear();
					size_t currentPos = currentRow.tellg();
					currentRow.seekg(0, std::ios::end);
					size_t endPos = currentRow.tellg();
					size_t remainingSymbolsCount = endPos - currentPos;
					currentRow.seekg(currentPos);

					char* remainder = new char[remainingSymbolsCount];
					currentRow.read(remainder, remainingSymbolsCount);

					MyString name(remainder);
					name = name.substr(0, remainingSymbolsCount);

					session.getTask(name);
				}
			}
		}
		else if (currentCommand == "list-tasks")
		{
			if (!session.isThereALoggedInUser())
			{
				std::cout << "Login or register in order to list tasks!" << std::endl;
			}
			else
			{
				MyString dueDate;
				currentRow >> dueDate;
				bool isDueDateValid = isValidDate(dueDate);

				tm tm = {};
				if (isDueDateValid)
				{
					std::stringstream ss(dueDate.c_str());
					ss >> std::get_time(&tm, "%Y-%m-%d");
					session.listTasks(mktime(&tm));
				}
				else
				{
					session.listAllTasks();
				}
			}
		}
		else if (currentCommand == "list-completed-tasks")
		{
			if (!session.isThereALoggedInUser())
			{
				std::cout << "Login or register in order to add tasks!" << std::endl;
			}
			else
			{
				session.listAllCompletedTasks();
			}
		}
		else if (currentCommand == "list-dashboard")
		{

		}
		else if (currentCommand == "finish-task")
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

					session.finishTask(taskId);

					std::cout << "Task started successfully!" << std::endl;
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
		else
		{
			std::cout << "Invalid command!" << std::endl;
			printHelpMenu(session.isThereALoggedInUser());
		}
	}

	std::cout << "Exited successfully!";
}