#include "Variable.h"

Variable::Variable() {

}

Variable::Variable(const Variable& copyVar) {
	type = copyVar.type;
	switch (type)
	{
	case DataType::INTEGER:
		pData = new int64_t;
		*(int64_t*)pData = *(int64_t*)copyVar.pData;
		break;
	case DataType::FLOAT:
		pData = new double;
		*(double*)pData = *(double*)copyVar.pData;
		break;
	case DataType::STRING:
		pData = new std::string(*(std::string*)copyVar.pData);
		break;
	}
}

Variable::Variable(int64_t value) {
	type = DataType::FLOAT;
	pData = new double;
	*(double*)pData = static_cast<double>(value);
}

Variable::Variable(const char* pString, uint32_t size) {
	type = DataType::STRING;
	pData = new std::string(pString, size);
}

Variable::Variable(double value) {
	type = DataType::FLOAT;
	pData = new double;
	*(double*)pData = value;
}

Variable::~Variable() {
	if (type == DataType::STRING) {
		delete (std::string*)pData;
	}
	else {
		delete pData;
	}

	
}

DataType Variable::getDataType() const {
	return type;
}

const void* Variable::getData() const {
	return pData;
}

Result Variable::constructFromArithmeticOperation(const Variable& var1, const Variable& var2, Operator operation) {
	if (var1.getDataType() == DataType::STRING and var2.getDataType() == DataType::STRING) {
		if (operation != Operator::ADD)
			return Result::ILLEGALOPERATIONERROR;
		type = DataType::STRING;
		pData = new std::string();
		*(std::string*)pData = *(std::string*)var1.getData() + *(std::string*)var2.getData();

		return Result::SUCCESS;
	}

	if (var1.getDataType() == DataType::FLOAT and var2.getDataType() == DataType::FLOAT) {
		type = DataType::FLOAT;
		pData = new double;
		switch (operation)
		{
		case Operator::ADD:
			*(double*)pData = *(double*)var1.getData() + *(double*)var2.getData();
			break;
		case Operator::SUBTRACT:
			*(double*)pData = *(double*)var1.getData() - *(double*)var2.getData();
			break;
		case Operator::MULTIPLY:
			*(double*)pData = *(double*)var1.getData() * *(double*)var2.getData();
			break;
		case Operator::DIVIDE:
			*(double*)pData = *(double*)var1.getData() / *(double*)var2.getData();
			break;
		}	
		return Result::SUCCESS;
	}


	return Result::ILLEGALOPERATIONERROR; //Damn you're screwed if you get this
}

void print(const Variable& value) {
	switch (value.getDataType())
	{
	case DataType::INTEGER:
		std::cout << *(int64_t*)value.getData() << "\n";
		break;
	case DataType::FLOAT:
		std::cout << *(double*)value.getData() << "\n";
		break;
	case DataType::STRING:
		std::cout << *(std::string*)value.getData() << "\n";
		break;

	}
}
