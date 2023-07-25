#pragma once
#include "defines.h"
#include "Token.h"

Result arithmeticOperation(const Variable& val1, Key key, const Variable& val2, Token& resultToken) {
	Variable value;
	Result result;
	result = value.constructFromArithmeticOperation(val1, val2, key);
	if (result != Result::SUCCESS)
		return result;

	
}