#include <cstdint> // std::intptr_tのため
#include <iostream>

extern "C" void unswafe_c_function(char* str)
{
	std::cout << "unsafe_c_function: " << str << std::endl;

} 

void unsafe_interface_function(void *data)
{
	
}