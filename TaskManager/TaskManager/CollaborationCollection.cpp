#include "CollaborationCollection.h"

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

void CollaborationCollection::readCollaborationsFromFile(const char* filename)
{

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

	return nullptr;
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
		collaborations[collaborationsCount - 1].~SharedPtr();
	}

	collaborationsCount--;
}

void CollaborationCollection::saveAllCollaborationsToFile(const char* filename)
{

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