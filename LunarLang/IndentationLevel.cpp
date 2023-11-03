#include "IndentationLevel.h"

IndentationLevel::IndentationLevel(uint32_t returnLine) {
    this->returnLine = returnLine;
}

bool IndentationLevel::contains(const std::string& variableName) {
    return variables.contains(variableName);
}

const Variable& IndentationLevel::getVariableValue(const std::string& variableName) {
    return variables[variableName];
}

void IndentationLevel::setVariableValue(const std::string& variableName, const Variable& value) {
    variables[variableName] = value;
    
}

uint32_t IndentationLevel::leave() {
    return returnLine;
}
