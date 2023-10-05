#pragma once
#include "defines.h"
#include "TokenList.h"
#include "Variable.h"
#include "ScopeManagerAccess.h"

class LunarLangInterpreter
{
public:
	Result interpret(const char* filename);

private:
	std::vector<std::string> lines;
	uint32_t currentLine;
	Result executeTokens(TokenList& tokenList);
};

