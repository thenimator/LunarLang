#include "LunarLangInterpreter.h"
#include <fstream>
#include <string>
#include "Token.h"
#include "constant.h"
#include "Output.h"

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
            break;
    default:
        return Result::SYNTAXERROR;
    }
}
