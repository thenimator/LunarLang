#pragma once
#include "defines.h"
#include "TokenListElement.h"
class TokenList
{
public:
	TokenList(const std::vector<Token>& tokens);
	//resets current to first after cutting
	void cutFirst(uint32_t count);
	bool isEmpty();
	bool sizeIs(uint32_t size);
	void push_back(const TokenListElement& newLast);
	void resetPointer();
	bool currentHasNext();
	void advancePointer();
	void replaceCurrentAndFollowing(const TokenListElement& replacement, uint32_t followingDeleteCount);
	TokenListElement getCurrentElement();
private:
	void insertFirst(const TokenListElement& token);
	TokenListElement* first = nullptr;
	TokenListElement* last = nullptr;
	TokenListElement* current = nullptr;
	TokenListElement* previous = nullptr;
};

