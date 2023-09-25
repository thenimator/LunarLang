#pragma once
#include "defines.h"
#include <memory>
enum class DataType {
	//Deprecated
	INTEGER,
	FLOAT,
	STRING,
	BOOL
};

//TODO: Remove variable type INT and change it to double
//TODO: Change name to "Value" as it better represents this class
class Variable
{
public:
	Variable();
	Variable(bool input);
	Variable(const Variable& copyVar);
	Variable& operator=(const Variable& copyVar);
	Variable(int64_t value);
	Variable(const char* pString, uint32_t size);
	Variable(double value);
	~Variable();
	DataType getDataType() const;
	const void* getData() const;
	[[nodiscard]] Result constructFromArithmeticOperation(const Variable& var1, const Variable& var2, Operator operation);

private:
	void becomeCopy(const Variable& copyVar);
	void destroy();
	uint8_t data[sizeof(std::string)];
	DataType type;
};

void print(const Variable& value);