#include <iostream>

#include "Data.hpp"
#include "Serializer.hpp"

int main()
{
    Data originalData;

    originalData.name = "Hanako";
    originalData.age = 4;
    originalData.next = NULL;

    Data* originalPtr = &originalData;

    uintptr_t raw = Serializer::serialize(originalPtr);
    Data* restoredPtr = Serializer::deserialize(raw);

    std::cout << "===== Pointer values =====" << std::endl;
    std::cout << "Original pointer: " << originalPtr << std::endl;
    std::cout << "Serialized value: " << raw << std::endl;
    std::cout << "Restored pointer: " << restoredPtr << std::endl;

    std::cout << std::endl;
    std::cout << "===== Pointer comparison =====" << std::endl;

    if (originalPtr == restoredPtr)
        std::cout << "SUCCESS: The pointers are identical." << std::endl;
    else
    {
        std::cout << "FAILURE: The pointers are different." << std::endl;
        return 1;
    }

    std::cout << std::endl;
    std::cout << "===== Restored data =====" << std::endl;
    std::cout << "Name: " << restoredPtr->name << std::endl;
    std::cout << "Age: " << restoredPtr->age << std::endl;
    std::cout << "Next: " << restoredPtr->next << std::endl;

    std::cout << std::endl;
    std::cout << "===== Same object test =====" << std::endl;

    restoredPtr->age += 1;

    std::cout << "Changed age through restoredPtr." << std::endl;
    std::cout << "originalData.age: " << originalData.age << std::endl;
    std::cout << "restoredPtr->age: " << restoredPtr->age << std::endl;

    if (originalData.age == restoredPtr->age)
        std::cout << "SUCCESS: Both access the same object." << std::endl;
    else
    {
        std::cout << "FAILURE: They do not access the same object."
                  << std::endl;
        return 1;
    }

    return 0;
}