#include "TokenList.h"
#include "ScopeManagerAccess.h"
#include "LulaErrorAccess.h"
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

TokenList::~TokenList() {

	TokenListElement* del = first;
	TokenListElement* next;
	while (del != nullptr) {
		next = first->next;
		delete del;
		del = next;
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
	
	result = calculateValue(first,nullptr);
	if (result != Result::SUCCESS)
		return result;
		
	
	//Last remaining Token must have a value
	if (getCurrentElement().getToken().getKey() == Key::VARIABLE) {
		//output = *(Variable*)getCurrentElement().getToken().getData();
		output = *(Variable*)first->token.getData();
		return Result::SUCCESS;
	}
	return Result::SYNTAXERROR;
		
	
}

TokenListElement& TokenList::getCurrentElement() {
	return *current;
}

Result TokenList::gainTokenValues() {
	if (getSize() == 0)
		return Result::SUCCESS;
	resetPointer();
	while (current != nullptr) {
		if (getCurrentElement().getToken().getKey() != Key::VARIABLENAME) {
			previous = current;
			current = current->getNext();
			continue;
		}
			
		Variable output;
		Result result = scopeManager.getVariableValue(*(std::string*)getCurrentElement().getToken().getData(), output);
		if (result != Result::SUCCESS)
			return result;

		TokenListElement replacement = TokenListElement(Token(output));
		replaceCurrentAndFollowing(replacement, 0);
		
		previous = current;
		current = current->getNext();
	}
	resetPointer();
	return Result::SUCCESS;
}

Result TokenList::executeOperations(TokenListElement* start, TokenListElement* pastEnd, OperationType type) {
	TokenListElement* localCurrent = start;
	TokenListElement* next = start->next;
	TokenListElement* nextNext;
	while (next != pastEnd) {
		if (next->getToken().getKey() != Key::OPERATOR) {
			return Result::SYNTAXERROR;
		}
		if (getOperationType(*(Operator*)next->getToken().getData()) == type) {
			nextNext = next->next;
			if (nextNext == nullptr) {
				return Result::SYNTAXERROR;
			}
			if (localCurrent->getToken().getKey() != Key::VARIABLE) {
				return Result::SYNTAXERROR;
			}
			if (nextNext->getToken().getKey() != Key::VARIABLE) {
				return Result::SYNTAXERROR;
			}
			Variable resultValue;
			Result result = resultValue.constructFromArithmeticOperation(*(Variable*)localCurrent->getToken().getData(), *(Variable*)nextNext->getToken().getData(),*(Operator*)next->getToken().getData());
			if (result != Result::SUCCESS)
				return result;
			Token resultToken(resultValue);
			localCurrent->token = std::move(resultToken);
			TokenListElement* bac = nextNext->getNext();
			delete next;
			delete nextNext;
			next = bac;
			localCurrent->next = next;
		}
		else {
			nextNext = next->next;
			if (nextNext == nullptr) {
				return Result::SYNTAXERROR;
			}
			localCurrent = nextNext;
			next = localCurrent->next;
		}
	}
	return Result::SUCCESS;


}

Result TokenList::calculateValue(TokenListElement* start, TokenListElement* pastEnd) {
	Result result;
	
	TokenListElement* last = nullptr;
	TokenListElement* localCurrent = start;
	int32_t currentBracketLevel = 0;
	TokenListElement* bracket = nullptr;
	TokenListElement* inBracketFirst = nullptr;
	TokenListElement* inBracketLast = nullptr;
	while (localCurrent != pastEnd) {
		if (localCurrent->getToken().getKey() == Key::BRACKET) {
			if (*(Bracket*)localCurrent->getToken().getData() == Bracket::OPENING) {
				currentBracketLevel++;
				if (currentBracketLevel == 1) {
					bracket = localCurrent;
					inBracketFirst = localCurrent->getNext();
					//programs crashes when given tokens " ( ) " instead of throwing an error. This should fix it
					if (inBracketFirst->getToken().getKey() == Key::BRACKET) {
						if (*(Bracket*)inBracketFirst->getToken().getData() == Bracket::CLOSING) {
							return Result::SYNTAXERROR;
						}
					}
				}
			} else {
				currentBracketLevel--;
				if (currentBracketLevel == 0) {
					inBracketLast = last;
					result = calculateValue(inBracketFirst, inBracketLast->next);
					if (result != Result::SUCCESS)
						return result;
					bracket->token = std::move(inBracketFirst->token);
					delete inBracketFirst;
					bracket->next = localCurrent->next;
					delete localCurrent;
					localCurrent = bracket;
				}
				//can probably be removed
				if (currentBracketLevel < 0) {
					LulaErrorCreateObject eLula;
					eLula.errorMessage = "Unexpected token ')' no matching opening bracked found";
					lulaError = std::move(eLula);
					eLula.errorType = ErrorType::SyntaxError;
					return Result::SYNTAXERROR;
				}
				
			}
		}

		last = localCurrent;
		localCurrent = localCurrent->getNext();
	}
	/* Check is unnecessary because the programs already throws an error
	if (currentBracketLevel != 0)
		return Result::SYNTAXERROR;
	*/

	result = executeOperations(start, pastEnd, OperationType::POINT);
	if (result != Result::SUCCESS)
		return result;
	result = executeOperations(start, pastEnd, OperationType::LINE);
	if (result != Result::SUCCESS)
		return result;
	result = executeOperations(start, pastEnd, OperationType::EQUALS);
	if (result != Result::SUCCESS)
		return result;
	result = executeOperations(start, pastEnd, OperationType::UNEQUALS);
	if (result != Result::SUCCESS)
		return result;
	result = executeOperations(start, pastEnd, OperationType::AND);
	if (result != Result::SUCCESS)
		return result;
	result = executeOperations(start, pastEnd, OperationType::OR);
	if (result != Result::SUCCESS)
		return result;

	

	return Result::SUCCESS;
	
}
