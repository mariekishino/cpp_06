#include "identify.hpp"

#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

static void printSeparator(void)
{
	std::cout << "--------------------------------" << std::endl;
}
static void testGeneratedObjects(void)
{
	std::cout << "===== GENERATED OBJECTS =====" << std::endl;

	for (int i = 0; i < 10; ++i)
	{
		Base* object = generate();

		printSeparator();

		std::cout << "Pointer type:    ";
		identify(object);

		std::cout << "Reference type:  ";
		identify(*object);

		delete object;
	}
}

static void testKnownObjectA(void)
{
	std::cout << std::endl;
	std::cout << "===== KNOWN OBJECT: A =====" << std::endl;

	A object;

	std::cout << "Expected: A" << std::endl;

	std::cout << "Pointer type:    ";
	identify(&object);

	std::cout << "Reference type:  ";
	identify(object);

	printSeparator();
}

static void testKnownObjectB(void)
{
	std::cout << std::endl;
	std::cout << "===== KNOWN OBJECT: B =====" << std::endl;

	B object;
	std::cout << "Expected: B" << std::endl;

	std::cout << "Pointer type:   ";
	identify(&object);

	std::cout << "Reference type: ";
	identify(object);

	printSeparator();
}


static void testKnownObjectC(void)
{
    std::cout << std::endl;
    std::cout << "===== KNOWN OBJECT: C =====" << std::endl;

    C object;

    std::cout << "Expected: C" << std::endl;

    std::cout << "Pointer type:   ";
    identify(&object);

    std::cout << "Reference type: ";
    identify(object);

    printSeparator();
}

static void testBaseObject(void)
{
	std::cout << std::endl;
	std::cout << "===== BASE OBJECT =====" << std::endl;

	Base object;

	std::cout << "Expected: Unknown" << std::endl;
	std::cout << "Pointer type   : ";
	identify(&object);

	std::cout << "Reference type : ";
	identify(object);

	printSeparator();
}

static void testNullPointer(void)
{
	std::cout << std::endl;
	std::cout << "===== NULL POINTER =====" << std::endl;

	Base* object = NULL;

	std::cout << "Expected: Unknown" << std::endl;

	std::cout << "Pointer type:   ";
	identify(object);

	// 未定義動作になる	
	// std::cout << "Reference type : ";
	// identify(*object);


	printSeparator();
}



int main(void)
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	testGeneratedObjects();
	testKnownObjectA();
	testKnownObjectB();
	testKnownObjectC();
	testBaseObject();
	testNullPointer();

	return 0;
}
