#pragma once
#include <iostream>

template <class T>
class Optional
{
public:
	Optional();
	Optional(const T& value);
	Optional(T&& value);

	bool isFilled() const;
	const T& getValue() const;
	T& getValue();
	void reset();
	bool operator==(const Optional<T>& other) const;
private:
	T data;
	bool hasValue;
};

template<class T>
Optional<T>::Optional() : hasValue(false) {}

template <class T>
Optional<T>::Optional(const T& value) : data(value), hasValue(true) {}

template <class T>
Optional<T>::Optional(T&& value) : data(std::move(value)), hasValue(true) {}

template<class T>
bool Optional<T>::isFilled() const
{
	return hasValue;
}

template<class T>
const T& Optional<T>::getValue() const
{
	if (!hasValue) {
		throw std::runtime_error("No value present");
	}

	return data;
}

template<class T>
T& Optional<T>::getValue()
{
	if (!hasValue) {
		throw std::runtime_error("No value present");
	}

	return data;
}

template<class T>
void Optional<T>::reset()
{
	hasValue = false;
	data = T();
}

template <class T>
bool Optional<T>::operator==(const Optional<T>& other) const {
	if (hasValue != other.hasValue) {
		return false;
	}
	if (!hasValue) {
		return true;
	}
	return data == other.data;
}