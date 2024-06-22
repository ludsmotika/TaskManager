#pragma once
#include "Collaboration.h"
#include "SharedPtr.hpp"

class CollaborationCollection
{
public:
	CollaborationCollection();

	CollaborationCollection(const CollaborationCollection& other);
	CollaborationCollection& operator=(const CollaborationCollection& other);

	CollaborationCollection(CollaborationCollection&& other) noexcept;
	CollaborationCollection& operator=(CollaborationCollection&& other) noexcept;

	~CollaborationCollection();

	void readCollaborationsFromFile(const char* filename);

	void addCollaboration(Collaboration* collaboration);
	void addCollaboration(const Collaboration& collaboration);

	size_t getCollaborationsCount() const;

	SharedPtr<Collaboration> getCollaborationById(unsigned id) const;
	SharedPtr<Collaboration> getCollaborationByName(MyString collabName) const; 
	unsigned getMaxCollaborationId() const;

	const Collaboration& operator[] (unsigned index) const;
	SharedPtr<Collaboration> operator[] (unsigned index);

	void removeCollaborationByIndex(unsigned index);

	void saveAllCollaborationsToFile(const char* filename);
private:
	SharedPtr<Collaboration>* collaborations;
	size_t collaborationsCount;
	size_t capacity;

	void free();
	void copyFrom(const CollaborationCollection& other);
	void moveFrom(CollaborationCollection&& other);
	void resize();

	void saveCollaborationToFile(std::ofstream& os, const Collaboration& task);
};