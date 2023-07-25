#pragma once
#include "defines.h"
#include "Token.h"
#include <memory>
enum class DataType {
	INTEGER,
	FLOAT,
	STRING
};

//TODO: Remove variable type INT and change it to double
class Variable
{
public:
	~Variable();
	[[nodiscard]] Result constructFromToken(const Token& token);
	DataType getDataType() const;
	bool isNumber() const;
	const void* getData() const;
	[[nodiscard]] Result constructFromArithmeticOperation(const Variable& var1, const Variable& var2, Key operation);

private:
	void constructFromStr(const Token& token);
	void constructFromInt(const Token& token);
	void* data;
	DataType type;
};

