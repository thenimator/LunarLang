#include "TokenList.h"

TokenList::TokenList() {

}

TokenList::TokenList(const std::vector<Token>& tokens) {
	if (tokens.size() > 0) {
		insertFirst(tokens[0]);
	}

	for (uint32_t i = 1; i < tokens.size(); i++) {
		push_back(tokens[i]);
	}
}

Result TokenList::fillFromLine(std::string line) {
	const char* cLine = line.data();
	int tokenStart = 0;
	int i;
	bool strConstantIsOpen = false;
	for (i = 0; i < line.size(); i++) {
		if ((tokenStart == i) and cLine[i] == ' ') {
			tokenStart++;
			continue;
		}
		if (cLine[i] == ' ' and !strConstantIsOpen) {
			Token tempToken;
			Result result = tempToken.generateFromString(cLine+tokenStart, i - tokenStart);
			if (result != Result::SUCCESS)
				return result;

			
			TokenListElement pushElement(tempToken);
			push_back(pushElement);
			tokenStart = i + 1;

		}

		if (cLine[i] == '"')
			strConstantIsOpen = !strConstantIsOpen;


	}
	if (cLine[i-1] != ' ') {
		Token tempToken;
		Result result = tempToken.generateFromString(cLine + tokenStart, i - tokenStart);
		if (result != Result::SUCCESS)
			return result;
		TokenListElement pushElement(tempToken);
		push_back(pushElement);
	}
	


	return Result::SUCCESS;
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

uint32_t TokenList::getSize() const {
	TokenListElement* iterator = first;
	uint32_t counter = 0;
	while (iterator != nullptr) {
		iterator = iterator->getNext();
		counter++;
	}
	return counter;
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
	if (first == nullptr) {
		insertFirst(newLast);
		return;
	}
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

const TokenListElement& TokenList::getCurrentElement() const {
	return *current;
}

void TokenList::insertFirst(const TokenListElement& token) {
	TokenListElement* heapNewLast = new TokenListElement(token.getToken());
	first = heapNewLast;
	current = heapNewLast;
	previous = nullptr;
	last = heapNewLast;
}

Result TokenList::generateValue(Variable& output) {
	Result result;
	while (getSize() != 1) {
		result = executeAdditions();
		if (result != Result::SUCCESS)
			return result;
	}
	if (getCurrentElement().getToken().getKey() == Key::VARIABLE) {
		output = *(Variable*)getCurrentElement().getToken().getData();
		return Result::SUCCESS;
	}
	return Result::SYNTAXERROR;
		
	
}

Result TokenList::executeAdditions() {
	resetPointer();
	return Result::IMPLEMENTATIONERROR;
}