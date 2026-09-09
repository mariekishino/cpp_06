/*
fromChar()
    ↓
char値を取得
    ↓
他の型へstatic_cast
    ↓
printChar()

printChar()
    ↓
charとして表示可能？
    ├─ YES → 'A'
    └─ NO  → Non displayable
*/


#include <iostream>
#include "ScalarConverter.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./convert <literal>" << std::endl;
		return 1;
	}
	ScalarConverter::convert(argv[1]);

	return 0;

}


/*
try:

./convert 0
./convert nan
./convert 42.0f

// Char

./convert a
./convert z
./convert '*'
./convert '+'

// ASCIIの境界

./convert 31
./convert 32
./convert 65
./convert 126
./convert 127

./convert 128
./convert 200

// INTの境界
./convert 2147483647
./convert -2147483648

./convert 2147483648
./convert -2147483649

./convert 999999999999999999999999999999999

// float -> intの切り捨て
./convert 42.9f
./convert 42.1f
./convert -42.9f
./convert -42.1f

// double -> int

./convert 42.9
./convert -42.9

// int範囲を超えるfloat/double
./convert 2147483648.0
./convert -2147483649.0
出力はこうなるはず：
char: impossible
int: impossible
float: ...
double: ...

double -> float overflow
./convert 999999999999999999999999999999999999999.0
(これはおよそ1e39)
float 最大値は3.4e38なのでfloatには大きすぎるがdoubleには入る
char: impossible
int: impossible
float: impossible
double: 1e+39 前後
*/