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
	Token& operator=(const Token& copyToken);
	Token& operator=(Token&& consumeToken);
private:
	void destroy();
	void becomeCopy(const Token& copyToken);
	Key key;
	void* pData = nullptr;
};



bool isVariableName(const char* data, uint32_t size);
bool isNumber(const char* data, uint32_t size);
bool isStringConstant(const char* data, uint32_t size);
bool isFunctionName(const char* data, uint32_t size);
