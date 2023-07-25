#pragma once
#include "defines.h"
#include "Variable.h"
class VariableManager
{
public:

private:
	std::unordered_map<std::string, Variable> variables;
};

