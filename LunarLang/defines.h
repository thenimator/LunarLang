#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>
#include <unordered_map>

#ifdef NDEBUG
#define DEBUG false
#else
#define DEBUG true
#endif 


//TODO change cases on all results
enum class Result {
	SUCCESS,
	SYNTAXERROR,
	UNKNOWNVARIABLEERROR,
	ERROR,
	IMPLEMENTATIONERROR,
	ILLEGALOPERATIONERROR,
	NoLowerScopeError
};

enum class ErrorType {
	NoError,
	SyntaxError,
	UnknownVariableError,
	ImplementationError,
	IllegalOperationError,
	NoLowerScopeError,
	UnexpectedDatatypeError,
	UnmatchedBracketError
};

enum class Key {
	//Data Type of pData is gonna be Operator
	OPERATOR,
	//Data Type of pData is gonna be Variable
	VARIABLE,
	//Data Type of pData is gonna be std::string
	VARIABLENAME,
	//Data Type of pData is gonna be std::string
	FUNCTIONNAME,
	//Data Type of pData is gonna be Bracket 
	BRACKET,

	EMPTY,
	//Data Type of pData is gonna be Conditional
	CONDITIONAL,

	INPUT,
	//Data type of pData is gonna be Bracket
	CURLYBRACKET,
	//Data type of pData is gonna be DataType
	DATATYPENAME,
	//Data type of pData is gonna be Separator
	SEPARATOR

};

enum class Separator {
	COMMA
};

enum class DataType {
	FLOAT,
	STRING,
	BOOL,
	//deprecated
	ANY,
	//deprecated
	INTEGER,
};

enum class Input {
	BASIC
};

enum class Conditional {
	IF,
	WHILE
};

enum class Bracket {
	OPENING,
	CLOSING
};

enum class Operator {
	ASSIGN,
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE,
	OUTPUT,
	EQUALS,
	UNEQUALS,
	AND,
	OR,
	LESSTHAN,
	GREATERTHAN,
	MODULO
};

enum class OperationType {
	POINT,
	LINE,
	AND,
	OR,
	EQUALS,
	UNEQUALS,
	COMPARISSON,
	MODULO
};

struct LineLocation {
	std::string filename;
	uint32_t line;
};

OperationType getOperationType(Operator op);
const char* operationString(Operator op);
const char* boolName(bool input);