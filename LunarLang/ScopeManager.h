#pragma once
#include "defines.h"
#include "Variable.h"
#include "ScopeAccessFrame.h"

class ScopeManager {
public:
	ScopeManager();
	void setVariableValue(const std::string& variabelName, const Variable& value, bool isGlobal);
	Result getVariableValue(const std::string& variableName, Variable& outputValue);
private:
	ScopeAccessFrame globalScope;
	std::vector<ScopeAccessFrame> scopes;
};