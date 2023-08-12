#pragma once
#include "defines.h"
#include "Variable.h"
#include <unordered_map>

struct IndentationLevelVariable {
	Variable var;
	uint32_t level;
};


class ScopeAccessFrame {
public:
	void increaseIndentationLevel();
	Result lowerIndentationLevel();
	bool containsVariable(const std::string& variableName);
	/*
	* Does not check if the variable actually exists. Always check if the variable exists first with function containsVariable
	*/
	Variable getVariableValue(const std::string& variableName);
	void setVariableValue(const std::string& variableName, const Variable& value);
	uint32_t getMaxIndentationlevel();
private:
	uint32_t maxIndentationLevel = 0;
	std::unordered_map<std::string, IndentationLevelVariable> variables;
};