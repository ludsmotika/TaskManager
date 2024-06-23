#include "CollaborationCollection.h"
#include <fstream>

CollaborationCollection::CollaborationCollection()
{
	capacity = 8;
	collaborationsCount = 0;
	collaborations = new SharedPtr<Collaboration>[capacity];
}

CollaborationCollection::CollaborationCollection(const CollaborationCollection& other)
{
	copyFrom(other);
}

CollaborationCollection& CollaborationCollection::operator=(const CollaborationCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

CollaborationCollection::CollaborationCollection(CollaborationCollection&& other) noexcept
{
	moveFrom(std::move(other));
}

CollaborationCollection& CollaborationCollection::operator=(CollaborationCollection&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

CollaborationCollection::~CollaborationCollection()
{
	free();
}

void CollaborationCollection::readCollaborationsFromFile(const char* filename, UsersCollection& usersCollection, TasksCollection& tasksCollection)
{
	if (!filename)
		throw std::invalid_argument("Nullptr passed as an argument");

	std::ifstream is(filename, std::ios::binary | std::ios::in);

	if (!is.is_open())
		throw std::invalid_argument("Cannot open file for reading!");

	while (true)
	{
		unsigned id;
		is.read((char*)&id, sizeof(unsigned));

		size_t collabNameLength;
		is.read((char*)&collabNameLength, sizeof(size_t));

		char* collabName = new char[collabNameLength];
		is.read(collabName, sizeof(char) * collabNameLength);

		size_t creatorNameLength;
		is.read((char*)&creatorNameLength, sizeof(size_t));

		char* creatorName = new char[creatorNameLength];
		is.read(creatorName, sizeof(char) * creatorNameLength);

		if (is.eof()) break;

		MyString parsedCollabName(collabName);
		MyString parsedCreatorName(creatorName);

		Collaboration* collab = new Collaboration(id, parsedCollabName.substr(0,collabNameLength), parsedCreatorName.substr(0, creatorNameLength));
		
		size_t workersCount;
		is.read((char*)&workersCount, sizeof(size_t));

		for (size_t i = 0; i < workersCount; i++)
		{
			size_t currentWorkingUserNameLength;
			is.read((char*)&currentWorkingUserNameLength, sizeof(size_t));

			char* currentWorkingUserName = new char[currentWorkingUserNameLength];
			is.read(currentWorkingUserName, sizeof(char) * currentWorkingUserNameLength);

			MyString parsedCurrentUsername(currentWorkingUserName);

			collab->addUser(usersCollection.getUserByUsername(parsedCurrentUsername.substr(0, currentWorkingUserNameLength)));
		}


		size_t tasksCount;
		is.read((char*)&tasksCount, sizeof(size_t));

		for (size_t i = 0; i < tasksCount; i++)
		{
			unsigned currentTaskId;
			is.read((char*)&currentTaskId, sizeof(unsigned));

			collab->addCollaborationTask(tasksCollection.getTaskById(currentTaskId));
		}

		addCollaboration(collab);

		delete[] collabName;
		delete[] creatorName;
	}
}

void CollaborationCollection::addCollaboration(Collaboration* collaboration)
{
	if (collaborationsCount == capacity)
		resize();

	collaborations[collaborationsCount++] = collaboration;
}

void CollaborationCollection::addCollaboration(const Collaboration& collaboration)
{
	addCollaboration(new Collaboration(collaboration));
}

size_t CollaborationCollection::getCollaborationsCount() const
{
	return collaborationsCount;
}

SharedPtr<Collaboration> CollaborationCollection::getCollaborationById(unsigned id) const
{
	for (size_t i = 0; i < collaborationsCount; i++)
	{
		if (collaborations[i]->getId() == id)
			return collaborations[i];
	}

	return nullptr;
}

SharedPtr<Collaboration> CollaborationCollection::getCollaborationByName(MyString collabName) const
{
	for (size_t i = 0; i < collaborationsCount; i++)
	{
		if (collaborations[i]->getName() == collabName)
			return collaborations[i];
	}

	return SharedPtr<Collaboration>();
}

unsigned CollaborationCollection::getMaxCollaborationId() const
{
	unsigned biggestId = 0;

	for (size_t i = 0; i < collaborationsCount; i++)
	{
		if (collaborations[i]->getId() > biggestId)
			biggestId = collaborations[i]->getId();
	}

	return biggestId;
}

const Collaboration& CollaborationCollection::operator[] (unsigned index) const
{
	return *collaborations[index];
}

SharedPtr<Collaboration> CollaborationCollection::operator[] (unsigned index)
{
	return collaborations[index];
}

void CollaborationCollection::removeCollaborationByIndex(unsigned index)
{
	if (index >= 0 && index < collaborationsCount)
	{
		std::swap(collaborations[index], collaborations[collaborationsCount - 1]);
		//collaborations[collaborationsCount - 1].~SharedPtr();
	}

	collaborationsCount--;
}

void CollaborationCollection::saveAllCollaborationsToFile(const char* filename)
{
	if (!filename)
		throw std::invalid_argument("Nullptr passed as a parameter!");

	std::ofstream os(filename, std::ios::out | std::ios::binary);

	if (!os.is_open())
		throw std::invalid_argument("Cannot open file for reading!");

	for (size_t i = 0; i < collaborationsCount; i++)
		collaborations[i]->saveToFile(os);
}

void CollaborationCollection::free()
{
	delete[] collaborations;
}

void CollaborationCollection::copyFrom(const CollaborationCollection& other)
{
	collaborations = new SharedPtr<Collaboration>[other.capacity];
	collaborationsCount = other.collaborationsCount;
	capacity = other.capacity;

	//TODO: check if this is working right
	for (size_t i = 0; i < collaborationsCount; i++)
		collaborations[i] = other.collaborations[i];
}

void CollaborationCollection::moveFrom(CollaborationCollection&& other)
{
	collaborationsCount = other.collaborationsCount;
	capacity = other.capacity;

	collaborations = other.collaborations;
	other.collaborations = nullptr;

	other.collaborationsCount = other.capacity = 0;
}

void CollaborationCollection::resize()
{
	SharedPtr<Collaboration>* newCollection = new SharedPtr<Collaboration>[capacity *= 2];
	for (size_t i = 0; i < collaborationsCount; i++)
		newCollection[i] = collaborations[i];
	delete[] collaborations;
	collaborations = newCollection;
}
