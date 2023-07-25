#pragma once
#include <string>
#include <vector>
#include "defines.h"
#include "Variable.h"

enum class Key {
	UNSET,
	ASSIGN,
	OPENBRACKET,
	CLOSEBRACKET,
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE,
	OUTPUT,
	VARIABLE,
	INTCONSTANT,
	STRCONSTANT,
	TEMPVARIABLE
};


//Needs to be refactored to allow for TEMPVARIABLE
class Token
{
public:
	Token();
	Token(Variable variable);
	Token(const char* dataStart, int size);
	Token(const Token& copyToken);
	~Token();
	Key getKey() const;
	Result generateKey();
	const char* getData() const;
	int getDataSize() const;
	bool hasValue() const;
	bool isBracket() const;
	bool isOpenBracket() const;
	bool isArithmeticOperator() const;
	bool isArtihmeticPointOperator() const;
	bool isArtihmeticLineOperator() const;

private:
	bool isAllLetters();
	bool isAllNumbers();
	bool isStringConstant();
	Key key;
	//needs to be null-terminated even though dataLen is separately saved
	char* data;
	int dataLen;

};


[[nodiscard]] Result fillTokenArray(const std::string& line, std::vector<Token>& tokenArray);

