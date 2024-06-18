#pragma once
#include <iostream>

template <typename T>
class Vector
{
public:
	Vector();
	Vector(const Vector<T>& other);
	const Vector<T>& operator= (const Vector<T>& other);
	Vector(Vector<T>&& other) noexcept;
	Vector<T>& operator= (Vector<T>&& other);

	~Vector();

	size_t size() const;
	bool empty() const;
	unsigned erase(unsigned index);
	void clear();
	size_t getCapacity() const;

	void insert(unsigned index, const T& element);
	void insert(unsigned index, T&& element);

	void push_back(const T& element);
	void push_back(T&& element);
	void pop_back();

	const T& operator[] (int index) const;
	T& operator[] (int index);

private:
	void free();
	void copyFrom(const Vector<T>& other);
	void moveFrom(Vector<T>&& other);
	void resize();
	T* elements = nullptr;
	size_t elementsCount = 0;
	size_t capacity = 4;
};

template<typename T>
Vector<T>::Vector()
{
	elements = new T[3];
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}

template<typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
void Vector<T>::moveFrom(Vector<T>&& other)
{
	this->elements = other.elements;
	other.elements = nullptr;

	this->capacity = other.capacity;
	other.capacity = 0;

	this->elementsCount = other.elementsCount;
	other.elementsCount = 0;
}

template<typename T>
Vector<T>& Vector<T>::operator= (Vector<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
const Vector<T>& Vector<T>::operator= (const Vector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
Vector<T>::~Vector()
{
	free();
}

template<typename T>
void Vector<T>::free()
{
	delete[] elements;
}

template<typename T>
void Vector<T>::pop_back()
{
	if (!size())
		throw std::logic_error("Empty vector");

	erase(size() - 1);
}

template<typename T>
void Vector<T>::push_back(const T& string)
{
	insert(size(), string);
}

template<typename T>
void Vector<T>::push_back(T&& string)
{
	insert(size(), std::move(string));
}

template<typename T>
void Vector<T>::insert(unsigned index, T&& element)
{
	if (index<0 || index > size())
		throw std::invalid_argument("Invalid index!");

	elementsCount++;

	if (elementsCount >= capacity)
		resize();

	for (size_t i = size() - 1; i > index; i--)
		elements[i] = std::move(elements[i - 1]);

	elements[index] = std::move(element);
}

template<typename T>
void Vector<T>::insert(unsigned index, const T& element)
{
	if (index<0 || index > size())
		throw std::invalid_argument("Invalid index!");

	elementsCount++;

	if (elementsCount >= capacity)
		resize();

	for (size_t i = size() - 1; i > index; i--)
		elements[i] = elements[i - 1];

	elements[index] = element;
}


template<typename T>
void Vector<T>::copyFrom(const Vector<T>& other)
{
	elements = new T[other.getCapacity()];

	for (size_t i = 0; i < other.size(); i++)
		elements[i] = other.elements[i];

	elementsCount = other.size();
	capacity = other.getCapacity();
}

template<typename T>
void Vector<T>::clear()
{
	free();
	elementsCount = 0;
	elements = new T[capacity];
}

template<typename T>
const T& Vector<T>::operator[] (int index) const
{
	return elements[index];
}

template<typename T>
T& Vector<T>::operator[] (int index)
{
	return elements[index];
}

template<typename T>
size_t Vector<T>::getCapacity() const
{
	return capacity;
}

template<typename T>
unsigned Vector<T>::erase(unsigned index)
{
	if (index < 0 || index >= size())
		throw std::invalid_argument("Invalid index!");

	for (size_t i = index; i < size() - 1; i++)
		elements[i] = elements[i + 1];

	elementsCount--;
	return index;
}

template<typename T>
bool Vector<T>::empty() const
{
	if (!elementsCount)
		return true;

	return false;
}


template<typename T>
size_t Vector<T>::size() const
{
	return elementsCount;
}

template<typename T>
void Vector<T>::resize()
{
	capacity *= 2;
	T* newElements = new T[capacity];

	for (size_t i = 0; i < size(); i++)
		newElements[i] = elements[i];

	delete[] elements;

	elements = newElements;
}