#pragma once
#include "defines.h"
#include <memory>
enum class DataType {
	//Deprecated
	INTEGER,
	FLOAT,
	STRING
};

//TODO: Remove variable type INT and change it to double
class Variable
{
public:
	Variable();
	Variable(const Variable& copyVar);
	Variable(int64_t value);
	Variable(const char* pString, uint32_t size);
	Variable(double value);
	~Variable();
	DataType getDataType() const;
	const void* getData() const;
	[[nodiscard]] Result constructFromArithmeticOperation(const Variable& var1, const Variable& var2, Operator operation);

private:
	uint8_t data[sizeof(std::string)];
	DataType type;
};

void print(const Variable& value);