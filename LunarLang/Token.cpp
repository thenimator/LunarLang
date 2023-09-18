#include "Token.h"
#include "Variable.h"
#include "ScopeManagerAccess.h"

Token::Token() {

}

Key Token::getKey() const {
	return key;
}

Result Token::generateFromString(const char* pStringToken, uint32_t size) {
	if (size == 0) 
		return Result::IMPLEMENTATIONERROR;
	
	if (size == 1 and pStringToken[0] == '+') {
		key = Key::OPERATOR;
		pData = new Operator;
		*(Operator*)pData = Operator::ADD;
		return Result::SUCCESS;
	}
	if (size == 1 and pStringToken[0] == '-') {
		key = Key::OPERATOR;
		pData = new Operator;
		*(Operator*)pData = Operator::SUBTRACT;
		return Result::SUCCESS;
	}
	if (size == 1 and pStringToken[0] == '*') {
		key = Key::OPERATOR;
		pData = new Operator;
		*(Operator*)pData = Operator::MULTIPLY;
		return Result::SUCCESS;
	}
	if (size == 1 and pStringToken[0] == '/') {
		key = Key::OPERATOR;
		pData = new Operator;
		*(Operator*)pData = Operator::DIVIDE;
		return Result::SUCCESS;
	}
	if (size == 1 and pStringToken[0] == '=') {
		key = Key::OPERATOR;
		pData = new Operator;
		*(Operator*)pData = Operator::ASSIGN;
		return Result::SUCCESS;
	}
	if (size == 1 and pStringToken[0] == '(') {
		key = Key::BRACKET;
		pData = new Bracket;
		*(Bracket*)pData = Bracket::OPENING;
		return Result::SUCCESS;
	}
	if (size == 1 and pStringToken[0] == ')') {
		key = Key::BRACKET;
		pData = new Bracket;
		*(Bracket*)pData = Bracket::CLOSING;
		return Result::SUCCESS;
	}
	if (size == 3) {
		if (pStringToken[0] == 'o' and pStringToken[1] == 'u' and pStringToken[2] == 't') {
			key = Key::OPERATOR;
			pData = new Operator;
			*(Operator*)pData = Operator::OUTPUT;
			return Result::SUCCESS;
		}
	}
	//Working until this point
	if (isNumber(pStringToken, size)) {
		key = Key::VARIABLE;
		int64_t mult = 1;
		int64_t result = 0;
		for (uint32_t i = 0; i < (size-1); i++) {
			result += (pStringToken[size - 1 - i]-'0') * mult;
			mult *= 10;
		}
		if (pStringToken[0] == '-') {
			result *= -1;
		}
		else {
			result += (pStringToken[0] - '0') * mult;
		}
		pData = new Variable(result);
		return Result::SUCCESS;
	}
	if (isStringConstant(pStringToken,size)) {
		key = Key::VARIABLE;
		pData = new Variable(pStringToken+1, size-2);
		return Result::SUCCESS;
	}
	if (isVariableName(pStringToken, size)) {
		key = Key::VARIABLENAME;
		pData = new std::string(pStringToken, size);
		return Result::SUCCESS;
	}

	return Result::SYNTAXERROR;
}

Token::Token(const Token& copyToken) {
	becomeCopy(copyToken);
}

Token::Token(const Variable& var) {
	key = Key::VARIABLE;
	pData = new Variable(var);
}

const void* Token::getData() const {
	return pData;
}

Token::~Token() {
	destroy();
}

Token& Token::operator=(const Token& copyToken) {
	
	destroy();
	becomeCopy(copyToken);
	return *this;
}

Token& Token::operator=(Token&& consumeToken) {
	destroy();
	pData = consumeToken.pData;
	consumeToken.pData = nullptr;
	key = consumeToken.key;
	consumeToken.key = Key::EMPTY;
	return *this;
}

void Token::destroy() {
	if (pData != nullptr) {
		switch (key)
		{
		case Key::VARIABLE:
			delete (Variable*)pData;
			break;
		case Key::VARIABLENAME:
			delete (std::string*)pData;
			break;
		case Key::FUNCTIONNAME:
			delete (std::string*)pData;
			break;
		case Key::OPERATOR:
			delete (Operator*)pData;
			break;
		case Key::BRACKET:
			delete (Bracket*)pData;
			break;
		}
	}
}

void Token::becomeCopy(const Token& copyToken) {
	key = copyToken.key;
	switch (key)
	{
	case Key::VARIABLE:
		pData = new Variable(*(Variable*)copyToken.getData());
		break;
	case Key::VARIABLENAME:
		pData = new std::string(*(std::string*)copyToken.getData());
		break;
	case Key::FUNCTIONNAME:
		pData = new std::string(*(std::string*)copyToken.getData());
		break;
	case Key::OPERATOR:
		pData = new Operator;
		*(Operator*)pData = *(Operator*)copyToken.getData();
		break;
	case Key::BRACKET:
		pData = new Bracket;
		*(Bracket*)pData = *(Bracket*)copyToken.getData();
		break;
	}
}

//currently only support all-char variable names
bool isVariableName(const char* data, uint32_t size) {
	for (uint32_t i = 0; i < size; i++) {
		if (!((data[i] <= 'Z' and data[i] >= 'A') or (data[i] <= 'z' and data[i] >= 'a'))) 
			return false;
	}
	return true;
}
//assumes size to not be 0
bool isNumber(const char* data, uint32_t size) {
	if (!(data[0] <= '9' and data[0] >= '0')) {
		if (!(data[0] == '-'))
			return false;
	}
	for (uint32_t i = 1; i < size; i++) {
		if (!(data[i] <= '9' and data[i] >= '0'))
			return false;
	}
	return true;
}

bool isStringConstant(const char* data, uint32_t size) {
	if (data[0] != '"')
		return false;
	if (data[size-1] != '"')
		return false;

	for (uint32_t i = 1; i < size-1; i++){
		if (data[i] == '"')
			return false;
	}


	return true;
}




