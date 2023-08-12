#include "ScopeAccessFrame.h"

void ScopeAccessFrame::increaseIndentationLevel() {
	maxIndentationLevel++;
}

Result ScopeAccessFrame::lowerIndentationLevel() {
	for (std::unordered_map<std::string, IndentationLevelVariable>::iterator it = variables.begin(); it != variables.end();) {
		if (it._Ptr->_Myval.second.level = maxIndentationLevel) {
			it = variables.erase(it);
		}
		else {
			it++;
		}
			
	}
	maxIndentationLevel--;
	if (maxIndentationLevel != -1)
		return Result::SUCCESS;
	return Result::NoLowerScopeError;
}

bool ScopeAccessFrame::containsVariable(const std::string& variableName) {
	return variables.contains(variableName);
}

Variable ScopeAccessFrame::getVariableValue(const std::string& variableName) {
	return variables[variableName].var;
}

void ScopeAccessFrame::setVariableValue(const std::string& variableName, const Variable& value) {
	variables[variableName] = { value,maxIndentationLevel };
}

uint32_t ScopeAccessFrame::getMaxIndentationlevel()
{
	return maxIndentationLevel;
}
