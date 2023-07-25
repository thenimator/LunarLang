#include "RValue.h"
#include "Variable.h"
#include "operations.h"

[[nodiscard]] Result RValue::constructFromToken(const Token& token) {
    return value.constructFromToken(token);
}

Result handleArithmeticPointOperations(TokenList& tokenList) {
    Result result;
    while (true) {
        TokenListElement* nextElement = tokenList.getCurrentElement().getNext();
        if (nextElement == nullptr) {
            break;
        }
        if (tokenList.getCurrentElement().getToken().isOpenBracket()) {
            tokenList.advancePointer();
            continue;
        }
        if (!tokenList.getCurrentElement().getToken().hasValue())
            return Result::SYNTAXERROR;

        if (nextElement->getToken().isArtihmeticPointOperator()) { //should probably be it's own function all this nesting is killing me
            TokenListElement* nextNextElement = nextElement->getNext();
            if (nextNextElement->getToken().isOpenBracket()) {
                tokenList.advancePointer();
                continue;
            }

            if (nextNextElement->getToken().hasValue()) {
                Token replacementToken;
                Variable val1;
                result = val1.constructFromToken(tokenList.getCurrentElement().getToken());
                if (result != Result::SUCCESS)
                    return Result::SYNTAXERROR;
                Variable val2;
                result = val2.constructFromToken(nextNextElement->getToken());
                if (result != Result::SUCCESS)
                    return Result::SYNTAXERROR;

                result = arithmeticOperation(val1, nextElement->getToken().getKey(), val2, replacementToken);
                if (result != Result::SUCCESS)
                    return result;
            }
            else {
                return Result::SYNTAXERROR;
            }

            //you left here
                
        }




        tokenList.advancePointer();
    }
    
    return Result::SUCCESS;
    
}

Result handleArtihmeticLineOperations(TokenList& tokenList) {

}

Result deleteUnusedBrackets(TokenList& tokenList) {

}

[[nodiscard]] Result generateRValue(RValue& rVal, TokenList& tokenList) {
    Result result;
    while (!tokenList.sizeIs(1)) {
        tokenList.resetPointer();

        result = handleArithmeticPointOperations(tokenList);
        if (result != Result::SUCCESS)
            return result;
    }
}
