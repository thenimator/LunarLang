#pragma once
#include "Variable.h"
#include "string"
#include "defines.h"
#include "Token.h"

class LunarLangInterpreter
{
public:
	Result interpret(const char* filename);

private:
	Result executeTokens(const std::vector<Token>& tokens);
};

