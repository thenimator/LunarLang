#pragma once
#include "defines.h"
#include "Token.h"

class TokenListElement
{
public:
	TokenListElement(const TokenListElement& copyElement);
	//check if passing by const reference is also possible
	TokenListElement(const Token& givenToken);
	~TokenListElement();
	bool hasNext();
	const Token& getToken() const;
	void setNext(TokenListElement* next);
	TokenListElement* getNext();
	const TokenListElement* getNext() const;
	Token token;
	TokenListElement* next = nullptr;
private:
	
};

