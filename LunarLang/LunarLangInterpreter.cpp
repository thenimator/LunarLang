#include "LunarLangInterpreter.h"
#include "TokenList.h"
#include "ScopeManagerAccess.h"

Result LunarLangInterpreter::interpret(const char* filename) {
    std::fstream file;
    file.open(filename, std::ios::in); 
    if (file.is_open()) {   
        std::string line;
        //char* line;
        while (getline(file, line)) { 
            TokenList tokenList;
            Result result = tokenList.fillFromLine(line);
            if (result != Result::SUCCESS)
                return result;

            result = executeTokens(tokenList);
            if (result != Result::SUCCESS)
                return result;
        }
        file.close(); 
    }

    return Result::SUCCESS;
}

//TODO: Export logic into functions instead of crowding this function
//NOTE: Maybe put this in tokenlist?
Result LunarLangInterpreter::executeTokens(TokenList& tokens) {
    Result result;
    if (tokens.getSize() == 0)
        return Result::SUCCESS;
    tokens.resetPointer();
    switch (tokens.getCurrentElement().getToken().getKey())
    {
    case Key::VARIABLENAME: {
        std::string variableName = *(std::string*)tokens.getCurrentElement().getToken().getData();
        if (!(tokens.getSize() > 2))
            return Result::SYNTAXERROR;

        if (tokens.getCurrentElement().getNext()->getToken().getKey() != Key::OPERATOR)
            return Result::SYNTAXERROR;
        Operator test = *(Operator*)tokens.getCurrentElement().getNext()->getToken().getData();
        TokenListElement* test2 = tokens.getCurrentElement().getNext();
        if (*(Operator*)tokens.getCurrentElement().getNext()->getToken().getData() != Operator::ASSIGN)
            return Result::SYNTAXERROR;

        tokens.cutFirst(2);
        result = tokens.gainTokenValues();
        if (result != Result::SUCCESS)
            return result;
        Variable output = Variable();
        result = tokens.generateValue(output);
        if (result != Result::SUCCESS)
            return result;

        scopeManager.setVariableValue(variableName, output, false);

           
    }
        break;

    case Key::OPERATOR: { //https://stackoverflow.com/questions/5136295/switch-transfer-of-control-bypasses-initialization-of-when-calling-a-function
        if (!((*(Operator*)(tokens.getCurrentElement().getToken().getData())) == Operator::OUTPUT))
            return Result::SYNTAXERROR;
        tokens.cutFirst(1);
        result = tokens.gainTokenValues();
        if (result != Result::SUCCESS)
            return result;
        Variable output = Variable();
        Result result = tokens.generateValue(output);
        if (result != Result::SUCCESS)
            return result;
        print(output);
    }
        

        break;

    case Key::FUNCTIONNAME:
        return Result::IMPLEMENTATIONERROR;
        break;

    case Key::VARIABLE:
        return Result::SYNTAXERROR;
        break;
    default:
        return Result::SYNTAXERROR;
    }

    return Result::SUCCESS;
}
