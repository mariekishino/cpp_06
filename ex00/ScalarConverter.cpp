#include "ScalarConverter.hpp"

#include <iostream>
#include <sstream>
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

static bool isDoublePseudo(const std::stirng &input)
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
			hasDot == true;
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

/*

これ明日：　
fromChar
fromInt
fromFloat
fromDouble
fromFloatPseudo
fromDoublePseudo
printImpossible
*/



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
		
		case TYPE_DOUBLE_PREUDO:
			fromDoublePseudo(argv_input);
			break;

		case TYPE_IVALID:
			printImpossible();
			break;
	}
}


