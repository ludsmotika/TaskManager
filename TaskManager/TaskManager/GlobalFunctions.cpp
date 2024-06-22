#include "GlobalFunctions.h"
#include <fstream>
#include <ctime>
#include <iostream>
#include <sstream>
#pragma warning (disable : 4996)

size_t getCharsCountInFile(const char* filename, char ch)
{
	if (!filename)
		throw std::invalid_argument("Nullptr passed!");

	std::ifstream ifs(filename, std::ios::binary);

	if (!ifs.is_open())
		throw std::invalid_argument("Cannot open file for reading!");

	size_t counter = 0;

	char currentChar;

	while (!ifs.eof())
	{
		ifs.read(&currentChar, sizeof(char));

		if (currentChar == ch)
			counter++;
	}

	return counter;
}

int getLengthToFirstCharOccurence(MyString str, char ch)
{
	int commandTextLength = -1;

	for (size_t i = 0; i < str.getSize(); i++)
	{
		if (str[i] == ' ')
			return i;
	}

	if (commandTextLength == -1)
		throw std::logic_error("The symbol you are searching for is not contained in the string!");
}

bool isValidDate(const MyString& date) {
	int year, month, day;
	char dash1, dash2;

	std::stringstream dateStream(date.c_str());
	dateStream >> year >> dash1 >> month >> dash2 >> day;

	if (!dateStream || dash1 != '-' || dash2 != '-')
		return false;

	if (month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	if (isLeap && month == 2) {
		if (day > 29)
			return false;
	}
	else {
		if (day > daysInMonth[month - 1])
			return false;
	}

	return true;
}

void printTime(time_t rawTime)
{
	struct tm* localTime = localtime(&rawTime);

	if (localTime == nullptr) {
		std::cerr << "Failed to convert time." << std::endl;
		return;
	}

	char buffer[80];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d", localTime);
	std::cout << buffer;
}

void printHelpMenu(bool isThereALoggedInUser)
{
	if (isThereALoggedInUser)
	{
		std::cout << std::endl;
		std::cout << "You can use the following commands!" << std::endl;
		std::cout << "add-task <name> <due_date> <description>" << std::endl;
		std::cout << "add-task <name> <description>" << std::endl;
		std::cout << "update-task-name <id> <name>" << std::endl;
		std::cout << "start-task <id>" << std::endl;
		std::cout << "update-task-description <id> <description>" << std::endl;
		std::cout << "remove-task-from-dashboard <id>" << std::endl;
		std::cout << "add-task-to-dashboard <id>" << std::endl;
		std::cout << "delete-task <id>" << std::endl;
		std::cout << "get-task <name>" << std::endl;
		std::cout << "get-task <id>" << std::endl;
		std::cout << "list-tasks <date>" << std::endl;
		std::cout << "list-tasks" << std::endl;
		std::cout << "list-completed-tasks" << std::endl;
		std::cout << "list-dashboard" << std::endl;
		std::cout << "finish-task <id>" << std::endl;
		std::cout << "logout" << std::endl;
	}
	else
	{
		std::cout << std::endl;
		std::cout << "You can use the following commands!" << std::endl;
		std::cout << "register <username> <password>" << std::endl;
		std::cout << "login <username> <password>" << std::endl;
		std::cout << "exit" << std::endl;
	}
}