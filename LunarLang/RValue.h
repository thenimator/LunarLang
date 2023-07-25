#pragma once
#include "defines.h"
#include "Token.h"
#include "Variable.h"
#include "TokenList.h"
class RValue
{
public:
	[[nodiscard]] Result constructFromToken(const Token& token);
private:
	Variable value;
};

//consumes tokelList
//sets rVal to the result
[[nodiscard]] Result generateRValue(RValue& rVal, TokenList& tokenList);