#pragma once
#include "defines.h"
#include "Variable.h"
#include "ScopeAccessFrame.h"

class ScopeManager {
public:
	ScopeManager();
	//needs to be given the current line if thre program is supposed to return to that point
	//this is the case in e.g. whiel loops
	void increaseIndentationLevel(uint32_t returnLine = 0);
	void increaseScopeLevel(uint32_t callerLine);
	//returns the line the program should go to after lowering the scope
	//if line is zero
	//this also automatically lowers the Scope
	uint32_t lowerIdentationLevel();
	void setVariableValue(const std::string& variabelName, const Variable& value, bool isGlobal);
	Result getVariableValue(const std::string& variableName, Variable& outputValue);
private:
	ScopeAccessFrame globalScope;
	std::vector<ScopeAccessFrame> scopes;
};