#pragma once
#include "defines.h"
#include "Variable.h"
#include "Function.h"
class FunctionManager {
public:
	bool hasFunction(const std::string& functionSignature);
	void addfunction(const std::string& functionSignature, const LineLocation& location);


private:
	std::unordered_map<std::string, LineLocation> functions;
};


