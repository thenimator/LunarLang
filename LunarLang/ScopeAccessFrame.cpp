#include "ScopeAccessFrame.h"

void ScopeAccessFrame::increaseIndentationLevel(uint32_t returnline) {
	indentations.push_back(IndentationLevel(returnline));
}

int ScopeAccessFrame::lowerIndentationLevel() {
	if (indentations.size() == 1) {
		return -static_cast<int>(indentations[0].leave());
	}
	return indentations[indentations.size() - 1].leave();
}

bool ScopeAccessFrame::containsVariable(const std::string& variableName) {
	for (uint32_t i = 0; i < indentations.size(); i++) {
		if (indentations[i].contains(variableName))
			return true;
	}
	return false;
}

Variable ScopeAccessFrame::getVariableValue(const std::string& variableName) {
	for (uint32_t i = 0; i < indentations.size(); i++) {
		if (indentations[i].contains(variableName))
			return indentations[i].getVariableValue(variableName);
	}
	if (DEBUG) {
		std::cout << "You messed up" << std::endl;
	}

	return Variable();
}

void ScopeAccessFrame::setVariableValue(const std::string& variableName, const Variable& value) {
	for (uint32_t i = 0; i < indentations.size(); i++) {
		if (indentations[i].contains(variableName)) {
			indentations[i].setVariableValue(variableName, value);
			return;
		}		
	}
	indentations[indentations.size() - 1].setVariableValue(variableName, value);
}
