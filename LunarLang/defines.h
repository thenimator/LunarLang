#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>

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
	NoLowerScopeError
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

	EMPTY

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
	OUTPUT
};

enum class OperationType {
	POINT,
	LINE
};

OperationType getOperationType(Operator op);