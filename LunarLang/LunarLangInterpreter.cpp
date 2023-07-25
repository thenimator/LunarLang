#include "LunarLangInterpreter.h"
#include <fstream>
#include <string>
#include "Token.h"
#include "constant.h"
#include "Output.h"
#include "TokenList.h"
#include "RValue.h"

Result LunarLangInterpreter::interpret(const char* filename) {
    std::fstream file;
    file.open(filename, std::ios::in); 
    if (file.is_open()) {   
        std::string line;
        //char* line;
        while (getline(file, line)) { 
            std::vector<Token> tokens;
            Result result = fillTokenArray(line,tokens);
            if (result != Result::SUCCESS)
                return result;

            result = executeTokens(tokens);
            if (result != Result::SUCCESS)
                return result;
        }
        file.close(); 
    }

    return Result::SUCCESS;
}

Result LunarLangInterpreter::executeTokens(const std::vector<Token>& tokens) {
    if (tokens.size() == 0)
        return Result::SUCCESS;
    switch (tokens[0].getKey())
    {
    case Key::OUTPUT:
        if (tokens.size() != 2)
            return Result::SYNTAXERROR;
        if (isConstant(tokens[1].getKey())) {
            printConstantValue(tokens[1]);
            return Result::SUCCESS;
        }
        return Result::ERROR;
            
        break;
    case Key::VARIABLE:
        if (tokens.size() < 3)
            return Result::SYNTAXERROR;
        if (tokens[1].getKey() != Key::ASSIGN)
            return Result::SYNTAXERROR;
        TokenList tokenList(tokens);
        tokenList.cutFirst(2);
        if (tokenList.isEmpty())
            return Result::SYNTAXERROR;
        
        
        break;
    default:
        return Result::SYNTAXERROR;
    }
}
