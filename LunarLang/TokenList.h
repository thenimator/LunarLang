#pragma once
#include "defines.h"
#include "TokenListElement.h"
#include "Variable.h"
class TokenList
{
public:
	TokenList();
	TokenList(const std::vector<Token>& tokens);
	Result fillFromLine(std::string line);
	//resets current to first after cutting
	void cutFirst(uint32_t count);
	bool isEmpty();
	uint32_t getSize() const;
	bool sizeIs(uint32_t size);
	void push_back(const TokenListElement& newLast);
	//sets current to the first element
	void resetPointer();
	bool currentHasNext();
	void advancePointer();
	Result generateValue(Variable& output);
	void replaceCurrentAndFollowing(const TokenListElement& replacement, uint32_t followingDeleteCount);
	const TokenListElement& getCurrentElement() const;
	TokenListElement& getCurrentElement();
private:
	
	Result executeLineOperations();
	//takes ownership of the TokenListElement
	void insertFirst(const TokenListElement& token);
	TokenListElement* first = nullptr;
	TokenListElement* last = nullptr;
	TokenListElement* current = nullptr;
	TokenListElement* previous = nullptr;
};

