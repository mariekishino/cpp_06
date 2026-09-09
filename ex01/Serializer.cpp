#include "Serializer.hpp"


// constructor & destructor
Serializer::Serializer(){}
Serializer::Serializer(Serializer const &other)
{
	*this = other;
}
Serializer::~Serializer(){}
Serializer &Serializer::operator=(Serializer const &other)
{
	if (this == &other)
		return (*this);
	return (*this);
}

uintptr_t Serializer::serialize(Data *ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data *Serializer::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}

