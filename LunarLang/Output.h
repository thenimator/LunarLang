#pragma once
#include "defines.h"
#include "Token.h"
void printConstantValue(const Token& token) {
	if (token.getKey() == Key::INTCONSTANT)
		std::cout << token.getData() << "\n";
	if (token.getKey() == Key::STRCONSTANT) {
		char* output = new char[token.getDataSize()-1];
		memcpy(output,token.getData()+1,token.getDataSize()-2);
		output[token.getDataSize()-2] = '\0';
		std::cout << output << "\n";
	}
}