#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
enum class Result {
	SUCCESS,
	SYNTAXERROR,
	UNKNOWNVARIABELERROR,
	ERROR,
	IMPLEMENTATIONERROR
};

enum class Key {
	//Data Type of pData is gonna be Operator
	OPERATOR,
	//Data Type of pData is gonna be Variable
	VARIABLE,
	//Data Type of pData is gonna be std::string
	VARIABLENAME,
	//Data Type of pData is gonna be std::string
	FUNCTIONNAME

};

enum class Operator {
	ASSIGN,
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE,
	OUTPUT
};