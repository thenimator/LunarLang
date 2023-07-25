#pragma once
#include "defines.h"
#include "Token.h"
class TokenListElement
{
public:
	const Token& getToken() const;
	TokenListElement(const Token& token);
	bool hasNext();
	void setNext(TokenListElement* next);
	TokenListElement* getNext();
private:
	TokenListElement* next = nullptr;
	Token token;
};

