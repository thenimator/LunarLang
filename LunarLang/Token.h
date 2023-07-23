#pragma once
#include <string>
#include <vector>
#include "defines.h"

enum class Key {
	ASSIGN,
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE,
	OUTPUT,
	VARIABLE,
	INTCONSTANT,
	STRCONSTANT
};



class Token
{
public:
	Token(const char* dataStart, int size);
	Token(const Token& copyToken);
	~Token();
	Key getKey() const;
	Result generateKey();
	const char* getData() const;
	int getDataSize() const;
private:
	bool isAllLetters();
	bool isAllNumbers();
	bool isStringConstant();
	Key key;
	char* data;
	int dataLen;

};


Result fillTokenArray(const std::string& line, std::vector<Token>& tokenArray);

