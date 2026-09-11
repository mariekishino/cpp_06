#include "identify.hpp"

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>

// static_cast is added for study purpose, upcast conversion is implicitly done
Base* generate(void)
{
	int randomValue = std::rand() % 3;

	if (randomValue == 0)
		return static_cast<Base*>(new A);
	if (randomValue == 1)
		return static_cast<Base*>(new B);
	return static_cast<Base*>(new C);
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p) != NULL)
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p) != NULL)
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p) != NULL)
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown" << std::endl;
}

void identify(Base& p)
{
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << std::endl;
		return;
	}
	catch(const std::exception&)
	{
		std::cout << "[A& cast failed]";
	}

	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << std::endl;
		return;
	}
	catch(const std::exception&)
	{
		std::cout << "[B& cast failed]";
	}
	
	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << std::endl;
		return;
	}
	catch(const std::exception&)
	{
		std::cout << "[C& cast failed]";
	}

	std::cout << "Unknown" << std::endl;
}

