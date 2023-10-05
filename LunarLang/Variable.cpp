#include "Variable.h"
#include "LulaErrorAccess.h"

Variable::Variable() {

}

Variable::Variable(bool input) {
	type = DataType::BOOL;
	*(bool*)&data = input;
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
		switch (operation)
		{
		case Operator::ADD: 
			type = DataType::STRING;
			//can't set string a to string b if string a is uninitialized
			new(data) std::string();
			*(std::string*)&data = *(std::string*)var1.getData() + *(std::string*)var2.getData();
			break;
		case Operator::EQUALS:
			type = DataType::BOOL;
			*(bool*)&data = *(std::string*)var1.getData() == *(std::string*)var2.getData();
			break;
		case Operator::UNEQUALS:
			type = DataType::BOOL;
			*(bool*)&data = *(std::string*)var1.getData() != *(std::string*)var2.getData();
			break;
		default:
			LulaErrorCreateObject eLula;
			eLula.errorMessage = std::string("Illegal operation string ") + operationString(operation) + " string.";
			lulaError = std::move(eLula);
			return Result::ILLEGALOPERATIONERROR;
			break;
		}
		

		return Result::SUCCESS;
	}

	if (var1.getDataType() == DataType::FLOAT and var2.getDataType() == DataType::FLOAT) {
		
		switch (operation)
		{
		case Operator::ADD:
			type = DataType::FLOAT;
			*(double*)&data = *(double*)var1.getData() + *(double*)var2.getData();
			break;
		case Operator::SUBTRACT:
			type = DataType::FLOAT;
			*(double*)&data = *(double*)var1.getData() - *(double*)var2.getData();
			break;
		case Operator::MULTIPLY:
			type = DataType::FLOAT;
			*(double*)&data = *(double*)var1.getData() * *(double*)var2.getData();
			break;
		case Operator::DIVIDE:
			type = DataType::FLOAT;
			*(double*)&data = *(double*)var1.getData() / *(double*)var2.getData();
			break;
		case Operator::EQUALS:
			type = DataType::BOOL;
			*(bool*)&data = *(double*)var1.getData() == *(double*)var2.getData();
			break;
		case Operator::UNEQUALS:
			type = DataType::BOOL;
			*(bool*)&data = *(double*)var1.getData() != *(double*)var2.getData();
			break;
		case Operator::LESSTHAN:
			type = DataType::BOOL;
			*(bool*)&data = *(double*)var1.getData() < *(double*)var2.getData();
			break;
		case Operator::GREATERTHAN:
			type = DataType::BOOL;
			*(bool*)&data = *(double*)var1.getData() > *(double*)var2.getData();
			break;
		default:
			LulaErrorCreateObject eLula;
			eLula.errorMessage = std::string("Illegal operation float ") + operationString(operation) + " float.";
			lulaError = std::move(eLula);
			return Result::ILLEGALOPERATIONERROR;
			break;
		}	
		return Result::SUCCESS;
	}
	if (var1.getDataType() == DataType::BOOL and var2.getDataType() == DataType::BOOL) {
		
		switch (operation)
		{
		case Operator::EQUALS:
			type = DataType::BOOL;
			*(bool*)&data = *(bool*)var1.getData() == *(bool*)var2.getData();
			break;
		case Operator::UNEQUALS:
			type = DataType::BOOL;
			*(bool*)&data = *(bool*)var1.getData() != *(bool*)var2.getData();
			break;
		case Operator::AND:
			type = DataType::BOOL;
			*(bool*)&data = *(bool*)var1.getData() and *(bool*)var2.getData();
			break;
		case Operator::OR:
			type = DataType::BOOL;
			*(bool*)&data = *(bool*)var1.getData() or *(bool*)var2.getData();
			break;
		default:
			LulaErrorCreateObject eLula;
			eLula.errorMessage = std::string("Illegal operation bool ") + operationString(operation) + " bool.";
			lulaError = std::move(eLula);
			return Result::ILLEGALOPERATIONERROR;
			break;
		}
		return Result::SUCCESS;
	}


	return Result::ILLEGALOPERATIONERROR; //Damn you're screwed if you get this
}

void Variable::becomeCopy(const Variable& copyVar) {
	type = copyVar.type;
	switch (type)
	{
	case DataType::FLOAT:
		*(double*)&data = *(double*)&copyVar.data;
		break;
	case DataType::STRING:
		//can't set string a to string b if string a is uninitialized
		new(data) std::string();
		*(std::string*)&data = (*(std::string*)&copyVar.data);
		break;
	case DataType::BOOL:
		*(bool*)&data = *(bool*)&copyVar.data;
		break;
	default:
		break;
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
	case DataType::BOOL:
		std::cout << boolName(*(bool*)value.getData()) << "\n";
		break;

	}
}
