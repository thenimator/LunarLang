#include "ScopeManager.h"

ScopeManager::ScopeManager() {
	scopes.push_back(ScopeAccessFrame());
}

void ScopeManager::setVariableValue(const std::string& variableName, const Variable& value, bool isGlobal) {
	if (!isGlobal) {
		scopes[scopes.size() - 1].setVariableValue(variableName, value);
	}
	globalScope.setVariableValue(variableName, value);
	return;
}

Result ScopeManager::getVariableValue(const std::string& variableName, Variable& outputValue) {
	if (scopes[scopes.size() - 1].containsVariable(variableName)) {
		outputValue = scopes[scopes.size() - 1].getVariableValue(variableName);
		return Result::SUCCESS;
	}
	if (globalScope.containsVariable(variableName)) {
		outputValue = globalScope.getVariableValue(variableName);
		return Result::SUCCESS;
	}
	return Result::UNKNOWNVARIABLEERROR;
}
