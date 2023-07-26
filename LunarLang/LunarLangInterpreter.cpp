#include "LunarLangInterpreter.h"
#include "TokenList.h"

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

Result LunarLangInterpreter::executeTokens(TokenList& tokens) {
    
    if (tokens.getSize() == 0)
        return Result::SUCCESS;
    tokens.resetPointer();
    switch (tokens.getCurrentElement().getToken().getKey())
    {
    case Key::VARIABLENAME:

        break;

    case Key::OPERATOR: { //https://stackoverflow.com/questions/5136295/switch-transfer-of-control-bypasses-initialization-of-when-calling-a-function
        if (!((*(Operator*)(tokens.getCurrentElement().getToken().getData())) == Operator::OUTPUT))
            return Result::SYNTAXERROR;
        tokens.cutFirst(1);
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
}
