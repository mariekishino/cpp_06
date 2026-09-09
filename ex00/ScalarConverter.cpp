#include "ScalarConverter.hpp"

#include <iostream>
#include <sstream> // for istringstream
#include <iomanip>
#include <limits>
#include <cctype>
#include <cmath>

/* CONSTRUCTORS DESTRUCTOR */

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &other){*this = other;}
ScalarConverter::~ScalarConverter(){};

ScalarConverter &ScalarConverter::operator=(ScalarConverter const &other)
{
	if (this == &other)
		return (*this);
	return (*this);
}

/* HELPER FUNCTIONS */

enum LiteralType
{
	TYPE_CHAR,
	TYPE_INT,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_FLOAT_PSEUDO,
	TYPE_DOUBLE_PSEUDO,
	TYPE_INVALID
};

// isFloatPreudo
// isDoublePreudo
// isChar

static bool isFloatPseudo(const std::string &input)
{
	return (
		input == "nanf"
		|| input == "+inff"
		|| input == "-inff"
	);
}

static bool isDoublePseudo(const std::string &input)
{
	return (
		input == "nan"
		|| input == "+inf"
		|| input == "-inf"
	);
}

static bool isChar(const std::string &input)
{
	if (input.length() == 1)
	{
		unsigned char c = static_cast<unsigned char>(input[0]);

		if (!std::isdigit(c) && std::isprint(c))
			return true;
	}
	if (input.length() == 3
		&& input[0] == '\''
		&& input[2] == '\'')
	{
		unsigned char c = static_cast<unsigned char>(input[1]);

		if (std::isprint(c))
			return true;
	}
	return false;
}

static bool isInt(const std::string &input)
{
	if (input.empty())
		return false;
	std::size_t i = 0;

	if (input[i] == '+' || input[i] == '-')
		++i;
	
	if (i == input.length())
		return false;
	
	while (i < input.length())
	{
		if (!std::isdigit(static_cast<unsigned char>(input[i])))
		{
			return false;
		}
		++i;
	}
	return true;
}

static bool isFloat(const std::string &input)
{
	if (input.length() < 2)
		return false;
	if (input[input.length() - 1] != 'f')
		return false;
	std::string number = input.substr(0, input.length() - 1);

	if (number.empty())
		return false;

	std::size_t i = 0;
	if (number[i] == '+' || number[i] == '-')
		++i;
	if (i == number.length())
		return false;
	
	bool hasDigit = false;
	bool hasDot = false;

	while (i < number.length())
	{
		if (std::isdigit(static_cast<unsigned char>(number[i])))
		{
			hasDigit = true;
		}
		else if (number[i] == '.' && !hasDot)
		{
			hasDot = true;
		}
		else
		{
			return false;
		}
		++i;
	}
	return hasDigit && hasDot;
}


static bool isDouble(const std::string &input)
{
	if (input.empty())
		return false;

	std::size_t i = 0;

	if (input[i] == '+' || input[i] == '-')
		++i;
	if (i == input.length())
		return false;
	
	bool hasDigit = false;
	bool hasDot = false;

	while (i < input.length())
	{
		if (std::isdigit(static_cast<unsigned char>(input[i])))
		{
			hasDigit = true;
		}
		else if (input[i] == '.' && !hasDot)
		{
			hasDot = true;
		}
		else
		{
			return false;
		}
		++i;
	}
	return hasDigit && hasDot;
}


static LiteralType detectType(const std::string &argv_input)
{
	if (isFloatPseudo(argv_input))
		return TYPE_FLOAT_PSEUDO;
	
	if (isDoublePseudo(argv_input))
		return TYPE_DOUBLE_PSEUDO;

	if (isChar(argv_input))
		return TYPE_CHAR;

	if (isInt(argv_input))
		return TYPE_INT;
	
	if (isFloat(argv_input))
		return TYPE_FLOAT;

	if (isDouble(argv_input))
		return TYPE_DOUBLE;

	return TYPE_INVALID;
}

/* Output helper functions */
static void printImpossible()
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: impossible" << std::endl;
	std::cout << "double: impossible" << std::endl;
}

/*
*==================================================
* PRINT
*==================================================
*/

static void printChar(bool possible, char value)
{
	if (!possible)
	{
		std::cout << "char: impossible" << std::endl;
		return ;
	}
	unsigned char c = static_cast<unsigned char>(value);

	if (!std::isprint(c))
	{
		std::cout << "char: Non displayable"
				  << std::endl;
		return ;
	}

	std::cout << "char: '"
			  << value
			  << "'"
			  << std::endl;
}
static void printInt(bool possible, int value)
{
	if (!possible)
	{
		std::cout << "int: impossible" 
				  << std::endl;
		return ;
	}
	std::cout << "int: "
			  << value
			  << std::endl;
}
/*
fixed, precision() -> p.1094

ios.unsetf(f) -> iosのフラグfをクリアする
*/
static void printFloat(bool possible, float value)
{
	if (!possible)
	{
		std::cout << "float: impossible" << std::endl;
		return ;
	}
	if (static_cast<double>(value) == std::floor(static_cast<double>(value)))
	{
		std::cout << "float: "
				  << std::fixed
				  << std::setprecision(1)
				  << value
				  << "f"
				  << std::endl;
	}
	else
	{
    	std::cout.unsetf(std::ios::floatfield);
		std::cout << "float: "
		 		  << std::setprecision(7)
				  << value
				  << "f"
				  << std::endl;
	}
}
/*
fixed を使うと、setprecision()は小数点以下を何桁表示するか、という意味になる

小数部分がない場合は、.0を必ず１桁表示にする

小数部分がある場合は、fixedは使わずに、doubleの有効数字をなるべく維持して表示する

*/
static void printDouble(bool possible, double value)
{
	if (!possible)
	{
		std::cout << "double: impossible" << std::endl;
		return ;
	}

	// valueに小数部分があるか？
	if (value == std::floor(value))
	{
		std::cout << "double: "
				  << std::fixed
				  << std::setprecision(1)
				  << value
				  << std::endl;
	}
	else
	{
		std::cout.unsetf(std::ios::floatfield);
		std::cout << "double: "
				  << std::setprecision(std::numeric_limits<double>::digits10)
				  << value
				  << std::endl;
	}
}

/*
*==================================================
*Conversion from Char
*==================================================
*/
static void fromChar(const std::string &input)
{
	char c;
	if (input.length() == 3)
		c = input[1];
	else
		c = input[0];

	int i = static_cast<int>(c);
	float f = static_cast<float>(c);
	double d = static_cast<double>(c);

	// printAll(type, input, c, i, f, d);
	printChar(true, c);
	printInt(true, i);
	printFloat(true, f);
	printDouble(true, d);
}

/*
*==========================================
* Conversion from Int
*==========================================
*/
/*
isstringstream  - Stroustrup C++ p.262 
input string stream -> stringを入力ストリームとして読むもの

numeric_limits　-> p.132, p.1162
実行環境の型が保持できる最小値、最大値を取得
ex)
constexpr float min = numeric_limits<float>::min(); // floatの正の最小値

std::numeric_limits<char>::min() -> -128
std::numeric_limits<char>::max() -> 127

ASCIIの最大値
decimal     127
octal       77
hexadecimal 7F
*/
static void fromInt(const std::string &input)
{
	std::istringstream stream(input);

	int i;
	
	stream >> i;

	// intのoverflowを検出
	if (stream.fail())
	{
		printImpossible();
		return ;
	}

	// min = -128, max = 127
	int charMin = 
		static_cast<int>(std::numeric_limits<char>::min());
	int charMax = 
		static_cast<int>(std::numeric_limits<char>::max());

	bool charPossible = (i >= charMin && i <= charMax);

	char c = 0;
	if (charPossible)
		c = static_cast<char>(i);

	float f =
		static_cast<float>(i);
	
	double d =
		static_cast<double>(i);
	
	printChar(charPossible, c);
	printInt(true, i);
	printFloat(true, f);
	printDouble(true, d);

}
/*
man 3 floor
man 3 ceil

*/
static void fromFloat(const std::string &input)
{
	std::size_t numberLength = input.length() - 1;
	std::string number = input.substr(0, numberLength);

	std::istringstream stream(number);

	float f;
	stream >> f;
	
	if (stream.fail())
	{
		printImpossible();
		return ;
	}

	double truncated;
	// float -> intにしたとき小数部分を０方向に捨てる、をcast前に再現
	// 正の数ならfloor, 負の数ならceil
	if (f < 0.0f)
		truncated = std::ceil(static_cast<double>(f));
	else
		truncated = std::floor(static_cast<double>(f));

	// intMin = -2147483648, intMax = 2147483647
	double intMin =	static_cast<double>(std::numeric_limits<int>::min());
	double intMax = static_cast<double>(std::numeric_limits<int>::max());
	bool isAboveIntMin = (truncated >= intMin);
	bool isBelowIntMax = (truncated <= intMax);
	bool intPossible = isAboveIntMin && isBelowIntMax;
	
	int i = 0;
	if (intPossible)
		i = static_cast<int>(f);

	// charMin = -128, charMax = 127
	double charMin = static_cast<double>(std::numeric_limits<char>::min());
	double charMax = static_cast<double>(std::numeric_limits<char>::max());
	bool isAboveCharMin = (truncated >= charMin);
	bool isBelowCharMax = (truncated <= charMax);
	bool charPossible = isAboveCharMin && isBelowCharMax;

	char c = 0;
	if (charPossible)
		c = static_cast<char>(f);

	double d = static_cast<double>(f);

	printChar(charPossible, c);
	printInt(intPossible, i);
	printFloat(true, f);
	printDouble(true, d);

}

static void fromDouble(const std::string &input)
{
	std::istringstream stream(input);

	double d;
	stream >> d;
	if (stream.fail())
	{
		printImpossible();
		return ;
	}

	double truncated;
	if (d < 0.0)
		truncated = std::ceil(d);
	else
		truncated = std::floor(d);

	double intMin = static_cast<double>(std::numeric_limits<int>::min());
	double intMax = static_cast<double>(std::numeric_limits<int>::max());
	bool isAboveIntMin = (truncated >= intMin);
	bool isBelowIntMax = (truncated <= intMax);
	bool intPossible = isAboveIntMin && isBelowIntMax;
	int i = 0;
	if (intPossible)
		i = static_cast<int>(d);

	double charMin = static_cast<double>(std::numeric_limits<char>::min());
	double charMax = static_cast<double>(std::numeric_limits<char>::max());
	bool isAboveCharMin = (truncated >= charMin);
	bool isBelowCharMax = (truncated <= charMax);
	bool charPossible = isAboveCharMin && isBelowCharMax;
	char c = 0;
	if(charPossible)
		c = static_cast<char>(d);
	
	double absoluteValue;
	if (d < 0.0)
		absoluteValue = -d;
	else
		absoluteValue = d;
	
	double floatMax = static_cast<double>(std::numeric_limits<float>::max());
	// 3.5 *10^38
	bool isWithinFloatRange = (absoluteValue <= floatMax);
	bool floatPossible = isWithinFloatRange;
	float f = 0.0f;
	if (floatPossible)
		f = static_cast<float>(d);

	printChar(charPossible, c);
	printInt(intPossible, i);
	printFloat(floatPossible, f);
	printDouble(true, d);
}

/*
Pseudo literals

*/

static void fromFloatPseudo(const std::string &input)
{
	float f;

	if (input == "nanf")
	{
		f = std::numeric_limits<float>::quiet_NaN();
	}
	else if (input == "+inff")
	{
		f = std::numeric_limits<float>::infinity();
	}
	else
	{
		f = -std::numeric_limits<float>::infinity();
	}
    double d =
        static_cast<double>(f);

    (void)d;

    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;

    if (input == "nanf")
    {
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;
    }
    else if (input == "+inff")
    {
        std::cout << "float: +inff" << std::endl;
        std::cout << "double: +inf" << std::endl;
    }
    else
    {
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
    }

}


static void fromDoublePseudo(const std::string &input)
{
    double d;

    if (input == "nan")
    {
        d =
            std::numeric_limits<double>::quiet_NaN();
    }
    else if (input == "+inf")
    {
        d =
            std::numeric_limits<double>::infinity();
    }
    else
    {
        d =
            -std::numeric_limits<double>::infinity();
    }

    /*
     * double -> float
     */

    float f =
        static_cast<float>(d);

    (void)f;

    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;

    if (input == "nan")
    {
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;
    }
    else if (input == "+inf")
    {
        std::cout << "float: +inff" << std::endl;
        std::cout << "double: +inf" << std::endl;
    }
    else
    {
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
    }
}


/* public static member funtion, convert*/
void ScalarConverter::convert(const std::string &argv_input)
{
	LiteralType type = detectType(argv_input);

	switch(type)
	{
		case TYPE_CHAR:
			fromChar(argv_input);
			break;
		
		case TYPE_INT:
			fromInt(argv_input);
			break;
		
		case TYPE_FLOAT:
			fromFloat(argv_input);
			break;

		case TYPE_DOUBLE:
			fromDouble(argv_input);
			break;

		case TYPE_FLOAT_PSEUDO:
			fromFloatPseudo(argv_input);
			break;
		
		case TYPE_DOUBLE_PSEUDO:
			fromDoublePseudo(argv_input);
			break;

		case TYPE_INVALID:
			printImpossible();
			break;
	}
}


