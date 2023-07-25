#include "TokenList.h"

TokenList::TokenList(const std::vector<Token>& tokens) {
	if (tokens.size() > 0) {
		insertFirst(tokens[0]);
	}

	for (uint32_t i = 1; i < tokens.size(); i++) {
		push_back(tokens[i]);
	}
}

void TokenList::cutFirst(uint32_t count) {
	for (uint32_t i = 0; i < count; i++) {
		TokenListElement* bac = first;
		first = first->getNext();
		delete bac;
	}
	resetPointer();
}

bool TokenList::isEmpty() {
	if (first == nullptr)
		return true;
	return false;
}

bool TokenList::sizeIs(uint32_t size) {
	TokenListElement* check = first;
	uint32_t counter = 0;
	while (check != nullptr) {
		counter++;
		check = check->getNext();
	}
	return (counter == size);
}

void TokenList::push_back(const TokenListElement& newLast) {
	TokenListElement* heapNewLast = new TokenListElement(newLast.getToken());
	last->setNext(heapNewLast);
	last = heapNewLast;
}

void TokenList::resetPointer() {
	previous = nullptr;
	current = first;
}

bool TokenList::currentHasNext() {
	return current->hasNext();
}

void TokenList::advancePointer() {
	previous = current;
	current = current->getNext();
}
//current will end up on the replacement
void TokenList::replaceCurrentAndFollowing(const TokenListElement& replacement, uint32_t followingDeleteCount) {
	TokenListElement* heapReplacement = new TokenListElement(replacement.getToken());
	TokenListElement* firstNotReplace = current->getNext();
	delete current;
	for (uint32_t i = 0; i < followingDeleteCount; i++) {
		TokenListElement* bac = firstNotReplace;
		firstNotReplace = firstNotReplace->getNext();
		delete bac;
	}
	if (previous == nullptr) {
		first = heapReplacement;
	}
	else {
		previous->setNext(heapReplacement);
	}
	heapReplacement->setNext(firstNotReplace);
	current = heapReplacement;


}

TokenListElement TokenList::getCurrentElement() {
	return *current;
}

void TokenList::insertFirst(const TokenListElement& token) {
	TokenListElement* heapNewLast = new TokenListElement(token.getToken());
	first = heapNewLast;
	current = heapNewLast;
	previous = nullptr;
	last->setNext(heapNewLast);
	last = heapNewLast;
}
