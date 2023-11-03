#include "FunctionManager.h"

bool FunctionManager::hasFunction(const std::string& functionSignature) {
    return functions.contains(functionSignature);
}

void FunctionManager::addfunction(const std::string& functionSignature, const LineLocation& location) {
    functions[functionSignature] = location;
}

