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
	type = DataType::INTEGER;
	pData = new int64_t;
	*(int64_t*)pData = value;
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
