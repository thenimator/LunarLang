#pragma once
#include "defines.h"

struct LulaErrorCreateObject
{
	ErrorType errorType;
	uint32_t errorLine;
	std::string errorMessage;
	std::string errorFilename;
};

class LulaError {
public:
	LulaError();
	const std::string& what();
	LulaError& operator=(LulaErrorCreateObject&& data);

private:
	ErrorType errorType;
	uint32_t errorLine;
	std::string errorMessage;
	std::string errorFilename;
};