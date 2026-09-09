#include <iostream>
#include <limits>

/*
man 3 isnan
man 3 isinf


*/

int main()
{
	float inf = std::numeric_limits<float>::infinity();
	float nan = std::numeric_limits<float>::quiet_NaN();

	std::cout << "inf: " << inf << std::endl;
	std::cout << "nan: " << nan << std::endl;

	return 0;
}