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
	uint32_t line();
	ErrorType type();
	const std::string& file();
	LulaError& operator=(LulaErrorCreateObject&& data);

private:
	ErrorType errorType;
	uint32_t errorLine;
	std::string errorMessage;
	std::string errorFilename;
};