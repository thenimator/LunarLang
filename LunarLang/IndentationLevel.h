#pragma once
#include "defines.h"
#include <unordered_map>
#include "Variable.h"
class IndentationLevel {
public:
	IndentationLevel(uint32_t returnLine);
	bool contains(const std::string& variableName);
	const Variable& getVariableValue(const std::string& variableName);
	void setVariableValue(const std::string& variableName, const Variable& value);
	uint32_t leave();


private:
	uint32_t returnLine;
	std::unordered_map<std::string, Variable> variables;
};

