#pragma once
#include "MyString.h"

size_t getCharsCountInFile(const char* filename, char ch);

int getLengthToFirstCharOccurence(MyString str, char ch);

bool isValidDate(const MyString& date);

void printTime(time_t rawTime);

void printHelpMenu(bool isThereALoggedInUser);