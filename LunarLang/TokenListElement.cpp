#include "TokenListElement.h"

const Token& TokenListElement::getToken() const {
	return token;
}

TokenListElement::TokenListElement(const Token& token) {
	this->token = token;
}

bool TokenListElement::hasNext() {
	if (next == nullptr)
		return false;
	return true;
}

void TokenListElement::setNext(TokenListElement* next) {
	this->next = next;
}

TokenListElement* TokenListElement::getNext() {
	return next;
}
