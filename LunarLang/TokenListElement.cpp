#include "TokenListElement.h"

const Token& TokenListElement::getToken() const {
	return token;
}

TokenListElement::TokenListElement(const TokenListElement& copyElement) {
	next = copyElement.next;
	token = copyElement.token;
}

TokenListElement::TokenListElement(const Token& givenToken) {
	token = givenToken;
}

TokenListElement::~TokenListElement() {

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

const TokenListElement* TokenListElement::getNext() const {
	return next;
}
