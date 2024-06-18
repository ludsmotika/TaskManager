#include "GlobalFunctions.h"
#include <fstream>


//Check if the functions works right
size_t getCharsCountInFile(const char* filename, char ch)
{
	if (!filename)
		throw std::invalid_argument("Nullptr passed!");

	std::ifstream ifs(filename , std::ios::binary);

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