#pragma once
#include <unordered_map>
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
	std::unordered_map<std::string,Variable> variables;
};

