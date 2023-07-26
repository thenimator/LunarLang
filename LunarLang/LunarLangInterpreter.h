#pragma once
#include "Variable.h"
#include "defines.h"
#include "TokenList.h"

class LunarLangInterpreter
{
public:
	Result interpret(const char* filename);

private:
	Result executeTokens(TokenList& tokenList);
};

