#include "Variable.h"

Variable::~Variable() {
	delete data;
}

[[nodiscard]] Result Variable::constructFromToken(const Token& token) {
	if (token.getKey() == Key::INTCONSTANT) {
		constructFromInt(token);
		return Result::SUCCESS;
	}
		
	if (token.getKey() == Key::STRCONSTANT) {
		constructFromStr(token);
		return Result::SUCCESS;
	}
	return Result::ERROR;

}

DataType Variable::getDataType() const {
	return type;
}

bool Variable::isNumber() const {
	switch (type)
	{
	case DataType::INTEGER:
		return true;
		break;
	case DataType::FLOAT:
		return true;
		break;
	default:
		return false;
		break;
	}
}

const void* Variable::getData() const {
	return data;
}

Result Variable::constructFromArithmeticOperation(const Variable& var1, const Variable& var2, Key operation) {
	if (var1.isNumber()) {
		if (!var2.isNumber())
			return Result::INCOMPATIBLEDATATYPEOPERATIONERROR;
		if (var1.getDataType() == DataType::FLOAT or var2.getDataType() == DataType::FLOAT) {
			type = DataType::FLOAT;
		}
		else {
			type = DataType::INTEGER;
		}
		switch (type)
		{
		case DataType::INTEGER:
			int64_t var1Val = *(const int64_t*)var1.getData();
			int64_t var2Val = *(const int64_t*)var2.getData();
			data = new int64_t;
			switch (operation)
			{
			case Key::ADD:
				*(int64_t*)data = var1Val + var2Val;
				break;
			case Key::SUBTRACT:
				*(int64_t*)data = var1Val - var2Val;
				break;
			case Key::MULTIPLY:
				*(int64_t*)data = var1Val * var2Val;
				break;
			case Key::DIVIDE:
				*(int64_t*)data = var1Val / var2Val;
				break;
			default:
				return Result::ERROR;
				break;
			}
			break;
		case DataType::FLOAT:
			double var1ValDouble;
			double var2ValDouble;
			if (var1.getDataType() == DataType::INTEGER) {
				var1ValDouble = *(const int64_t*)var1.getData();
			}
			else {
				var1ValDouble = *(const double*)var1.getData();
			}
			if (var2.getDataType() == DataType::INTEGER) {
				var2ValDouble = *(const int64_t*)var2.getData();
			}
			else {
				var2ValDouble = *(const double*)var2.getData();
			}

			data = new double;
			switch (operation)
			{
			case Key::ADD:
				*(double*)data = var1ValDouble + var2ValDouble;
				break;
			case Key::SUBTRACT:
				*(double*)data = var1ValDouble - var2ValDouble;
				break;
			case Key::MULTIPLY:
				*(double*)data = var1ValDouble * var2ValDouble;
				break;
			case Key::DIVIDE:
				*(double*)data = var1ValDouble / var2ValDouble;
				break;
			default:
				break;
			}
			break;;
		}
		return Result::SUCCESS;
	}

	if (var1.getDataType() == DataType::STRING and var2.getDataType() == DataType::STRING) {
		type = DataType::STRING;
		if (!(operation == Key::ADD))
			return Result::BADOPERATIONERROR;
		data = new std::string;
		*(std::string*)data = *(std::string*)var1.getData() + *(std::string*)var2.getData();
		return Result::SUCCESS;
	}

	return Result::INCOMPATIBLEDATATYPEOPERATIONERROR;
}

void Variable::constructFromStr(const Token& token) {
	type = DataType::STRING;
	char* extract = new char[token.getDataSize() + 1];
	memcpy(extract, token.getData(), token.getDataSize());
	extract[token.getDataSize()] == '\0';
	data = new std::string(extract);
}

void Variable::constructFromInt(const Token& token) {
	type = DataType::INTEGER;
	data = new int64_t;
	int64_t mult = 1;
	*((int64_t*)data) = 0;
	for (uint32_t i = token.getDataSize() - 1; i >= 0; i--) {
		if (i == 0 and token.getData()[i] == '-') {
			*((int64_t*)data) = -1 * *((int64_t*)data);
			break;
		}
		*((int64_t*)data) = mult * token.getData()[i] + *((int64_t*)data);
		mult = mult * 10;
	}
}
