#include "Variable.h"

Variable::Variable() {

}

Variable::Variable(const Variable& copyVar) {
	becomeCopy(copyVar);
}

Variable& Variable::operator=(const Variable& copyVar) {
	destroy();
	becomeCopy(copyVar);

	return *this;
}

Variable::Variable(int64_t value) {
	type = DataType::FLOAT;
	*(double*)&data = static_cast<double>(value);
}

Variable::Variable(const char* pString, uint32_t size) {
	type = DataType::STRING;
	//https://stackoverflow.com/questions/222557/what-uses-are-there-for-placement-new
	new(data) std::string(pString, size);
}

Variable::Variable(double value) {
	type = DataType::FLOAT;
	*(double*)&data = value;
}

Variable::~Variable() {
	destroy();
}

DataType Variable::getDataType() const {
	return type;
}

//returns a pointer to the data
const void* Variable::getData() const {
	return data;
}

Result Variable::constructFromArithmeticOperation(const Variable& var1, const Variable& var2, Operator operation) {
	if (var1.getDataType() == DataType::STRING and var2.getDataType() == DataType::STRING) {
		if (operation != Operator::ADD)
			return Result::ILLEGALOPERATIONERROR;
		type = DataType::STRING;
		//can't set string a to string b if string a is uninitialized
		new(data) std::string();
		*(std::string*)&data = *(std::string*)var1.getData() + *(std::string*)var2.getData();

		return Result::SUCCESS;
	}

	if (var1.getDataType() == DataType::FLOAT and var2.getDataType() == DataType::FLOAT) {
		type = DataType::FLOAT;
		switch (operation)
		{
		case Operator::ADD:
			*(double*)&data = *(double*)var1.getData() + *(double*)var2.getData();
			break;
		case Operator::SUBTRACT:
			*(double*)&data = *(double*)var1.getData() - *(double*)var2.getData();
			break;
		case Operator::MULTIPLY:
			*(double*)&data = *(double*)var1.getData() * *(double*)var2.getData();
			break;
		case Operator::DIVIDE:
			*(double*)&data = *(double*)var1.getData() / *(double*)var2.getData();
			break;
		}	
		return Result::SUCCESS;
	}


	return Result::ILLEGALOPERATIONERROR; //Damn you're screwed if you get this
}

void Variable::becomeCopy(const Variable& copyVar) {
	type = copyVar.type;
	if (type == DataType::STRING) {
		//can't set string a to string b if string a is uninitialized
		new(data) std::string();
		*(std::string*)&data = (*(std::string*)&copyVar.data);
	}
	if (type == DataType::FLOAT) {
		*(double*)&data = *(double*)&copyVar.data;
	}
}

void Variable::destroy() {
	if (type == DataType::STRING) {
		//placement new https://stackoverflow.com/questions/55892372/unable-to-manually-call-destructor-of-stdstring
		std::string debughelp = *(std::string*)&data;
		(*(std::string*)&data).~basic_string();
	}
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
