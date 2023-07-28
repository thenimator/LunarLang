#pragma once
#include "defines.h"
#include "Variable.h"

class Token
{
public:
	Token();
	Token(const Token& copyToken);
	Token(const Variable& var);
	Key getKey() const;
	Result generateFromString(const char* pStringToken, uint32_t size);
	const void* getData() const;
	~Token();
	//https://stackoverflow.com/questions/28122942/why-is-copy-constructor-not-called-here
	//WTF? Copy assignment and copy constructor are not the same? Copy assignment is called every time an assignment is made while copy construction only if the object didnt exist
	Token& operator=(const Token& copyToken);
private:
	void becomeCopy(const Token& copyToken);
	Key key;
	void* pData = nullptr;
};



bool isVariableName(const char* data, uint32_t size);
bool isNumber(const char* data, uint32_t size);
bool isStringConstant(const char* data, uint32_t size);
