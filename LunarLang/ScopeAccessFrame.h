#pragma once
#include "defines.h"
#include "Variable.h"
#include "IndentationLevel.h"
#include <unordered_map>

class ScopeAccessFrame {
public:
	void increaseIndentationLevel(uint32_t returnline = 0);
	//return the line the program should return to
	//a negative value indicates that this ScopeAccessFrame should be destroyed
	int lowerIndentationLevel();
	bool containsVariable(const std::string& variableName);
	/*
	* Does not check if the variable actually exists. Always check if the variable exists first with function containsVariable
	*/
	Variable getVariableValue(const std::string& variableName);
	void setVariableValue(const std::string& variableName, const Variable& value);
private:
	std::vector<IndentationLevel> indentations;
};