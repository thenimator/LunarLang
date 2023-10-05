#include "ScopeManager.h"

ScopeManager::ScopeManager() {
	increaseScopeLevel(0);
	globalScope.increaseIndentationLevel(0);
}

void ScopeManager::increaseIndentationLevel(uint32_t returnLine) {
	scopes[scopes.size() - 1].increaseIndentationLevel(returnLine);
}

void ScopeManager::increaseScopeLevel(uint32_t callerLine) {
	scopes.push_back(ScopeAccessFrame());
	scopes[scopes.size() - 1].increaseIndentationLevel(callerLine);
}

uint32_t ScopeManager::lowerIdentationLevel() {
	int returnLine = scopes[scopes.size() - 1].lowerIndentationLevel();
	if (returnLine < 0) {
		scopes.pop_back();
		returnLine = -returnLine;
	}
	return returnLine;
}

void ScopeManager::setVariableValue(const std::string& variableName, const Variable& value, bool isGlobal) {
	if (!isGlobal) {
		scopes[scopes.size() - 1].setVariableValue(variableName, value);
		return;
	}
	globalScope.setVariableValue(variableName, value);
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
