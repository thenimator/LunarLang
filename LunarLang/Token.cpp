#include "Token.h"

Token::Token(const char* dataStart, int size) {
	dataLen = size;
	data = new char[size+1];
	memcpy(data,dataStart,size);
	data[size] = '\0';
}

Token::Token(const Token& copyToken) {
	key = copyToken.key;
	dataLen = copyToken.dataLen;
	data = new char[dataLen + 1];
	memcpy(data, copyToken.data, dataLen + 1);
}

Token::~Token() {
	delete data;
}

Result Token::generateKey() {
	if (dataLen == 1 and data[0] == '+') {
		key = Key::ADD;
		return Result::SUCCESS;
	}
	if (dataLen == 1 and data[0] == '-') {
		key = Key::SUBTRACT;
		return Result::SUCCESS;
	}
	if (dataLen == 1 and data[0] == '*') {
		key = Key::MULTIPLY;
		return Result::SUCCESS;
	}
	if (dataLen == 1 and data[0] == '/') {
		key = Key::DIVIDE;
		return Result::SUCCESS;
	}
	if (dataLen == 1 and data[0] == '=') {
		key = Key::ASSIGN;
		return Result::SUCCESS;
	}
	if (strcmp(data,"out") == 0) {
		key = Key::OUTPUT;
		return Result::SUCCESS;
	}
	if (isAllLetters()) {
		key = Key::VARIABLE;
		return Result::SUCCESS;
	}
	if (isAllNumbers()) {
		key = Key::INTCONSTANT;
		return Result::SUCCESS;
	}
	if (isStringConstant()) {
		key = Key::STRCONSTANT;
		return Result::SUCCESS;
	}

	return Result::SYNTAXERROR;
}

const char* Token::getData() const {
	return data;
}

int Token::getDataSize() const
{
	return dataLen;
}

bool Token::isAllLetters() {
	for (uint32_t i = 0; i < dataLen; i++) {
		if (!((data[i] <= 'Z' and data[i] >= 'A') or (data[i] <= 'z' and data[i] >= 'a'))) 
			return false;
	}
	return true;
}

bool Token::isAllNumbers() {
	for (uint32_t i = 0; i < dataLen; i++) {
		if (!(data[i] <= '9' and data[i] >= '0'))
			return false;
	}
	return true;
}

bool Token::isStringConstant() {
	if (data[0] != '"')
		return false;
	if (data[dataLen-1] != '"')
		return false;

	for (uint32_t i = 1; i < dataLen-1; i++){
		if (data[i] == '"')
			return false;
	}


	return true;
}

Key Token::getKey() const {
	return key;
}


Result fillTokenArray(const std::string& line, std::vector<Token>& tokenArray) {
	const char* cLine = line.data();
	int tokenStart = 0;
	int i;
	bool strConstantIsOpen = false;
	for (i = 0; i < line.size(); i++) {
		if (cLine[i] == ' ' and !strConstantIsOpen) {
			Token tempToken(cLine + tokenStart, i - (tokenStart));
			Result result = tempToken.generateKey();
			if (result != Result::SUCCESS)
				return result;

			tokenArray.push_back(tempToken);
			tokenStart = i + 1;

		}

		if (cLine[i] == '"')
			strConstantIsOpen = !strConstantIsOpen;


	}
	Token tempToken(cLine + tokenStart, i - (tokenStart));
	Result result = tempToken.generateKey();
	if (result != Result::SUCCESS)
		return result;

	tokenArray.push_back(tempToken);


	return Result::SUCCESS;

}