#include "LunarLangInterpreter.h"
#include "TokenList.h"
#include "ScopeManagerAccess.h"
#include "LulaErrorAccess.h"
#include "FunctionManagerAccess.h"
#include "Function.h"

uint32_t findMatchingCurlyBracketLine(const std::vector<std::string>& lines, uint32_t currentLine) {
    uint32_t indentation = 1;
    while (currentLine < lines.size()) {
        for (uint32_t i = 0; i < lines[currentLine].size(); i++) {
            if (lines[currentLine][i] == '{') {
                indentation++;
            }
            if (lines[currentLine][i] == '}') {
                indentation--;
                if (indentation == 0) {
                    return currentLine;
                }
            }

        }
        currentLine++;
    }
    return 0;
}

Result LunarLangInterpreter::interpret(const char* filename) {
    LulaErrorCreateObject reset;
    reset.errorLine = 0;
    reset.errorMessage = "";
    reset.errorType = ErrorType::NoError;
    reset.errorFilename = "";
    lulaError = std::move(reset);

    std::fstream file;
    file.open(filename, std::ios::in); 
    if (!file.is_open())
        return Result::ERROR; //improve this error
    
        
    std::string line;
    while (getline(file, line)) { 
        lines.push_back(std::move(line));
            
            
                
    }
    currentLine = 0;
    //tokens are responsible for changing currentline
    while (currentLine != lines.size()) {
        line = lines[currentLine];
        TokenList tokenList;
        Result result = tokenList.fillFromLine(line);
        if (result != Result::SUCCESS) {
            LulaErrorCreateObject error;
            error.errorFilename = filename;
            error.errorLine = currentLine+1;
            error.errorMessage = lulaError.what();
            error.errorType = lulaError.type();
            lulaError = std::move(error);

            return result;
        }


        result = executeTokens(tokenList);
        if (result != Result::SUCCESS) {
            LulaErrorCreateObject error;
            error.errorFilename = filename;
            error.errorLine = currentLine;
            error.errorMessage = lulaError.what();
            error.errorType = lulaError.type();
            lulaError = std::move(error);
            return result;
        }
    }
    file.close(); 
    

    return Result::SUCCESS;
}

//TODO: Export logic into functions instead of crowding this function
//NOTE: Maybe put this in tokenlist?
Result LunarLangInterpreter::executeTokens(TokenList& tokens) {
    Result result;
    if (tokens.getSize() == 0) {
        currentLine++;
        return Result::SUCCESS;
    }
        
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
        currentLine++;
           
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
        currentLine++;
    }
        

        break;
    case Key::INPUT: {
        if (tokens.getSize() == 1) {
            std::string temp;
            std::cin.ignore();
            std::getline(std::cin, temp);
            currentLine++;
            return Result::SUCCESS;
        }
        if (tokens.getSize() != 2) {
            return Result::SYNTAXERROR;
        }
        tokens.cutFirst(1);
        if (tokens.getCurrentElement().getToken().getKey() != Key::VARIABLENAME) {
            return Result::SYNTAXERROR;
        }
        std::string variableName = *(std::string*)tokens.getCurrentElement().getToken().getData();
        std::string input;
        std::cin.ignore();
        std::getline(std::cin,input);
        Variable output(input.c_str(),input.size());
        scopeManager.setVariableValue(variableName, output, false);
        currentLine++;

    }
        break;
    case Key::CONDITIONAL: {
        Conditional cond = *(Conditional*)tokens.getCurrentElement().getToken().getData();
        tokens.cutFirst(1);
        TokenListElement* current = tokens.getCurrentElement().next;
        TokenListElement* last = &tokens.getCurrentElement(); //hack tokens should be changed
        while (current->next != nullptr) {
            last = current;
            current = current->next;
        }
        if (current->getToken().getKey() != Key::CURLYBRACKET) {
            LulaErrorCreateObject createError;
            createError.errorMessage = "Expected token '{' at end of conditional statement";
            createError.errorType = ErrorType::SyntaxError;
            lulaError = std::move(createError);
            return Result::SYNTAXERROR;
        }
        if (*(Bracket*)current->getToken().getData() != Bracket::OPENING) {
            LulaErrorCreateObject createError;
            createError.errorMessage = "Unexpected token '}' at end of conditional statement";
            createError.errorType = ErrorType::SyntaxError;
            lulaError = std::move(createError);
            return Result::SYNTAXERROR;
        }
        delete current;
        last->next = nullptr;
        //the remaining tokens just have to be evaluated

        result = tokens.gainTokenValues(); //this is used very frequently could be moved to it's own function
        if (result != Result::SUCCESS)
            return result;
        Variable output = Variable();
        Result result = tokens.generateValue(output);
        if (result != Result::SUCCESS)
            return result;
        if (output.getDataType() != DataType::BOOL) {
            LulaErrorCreateObject createError;
            createError.errorMessage = "Unexpected data type after conditional statement";
            createError.errorType = ErrorType::UnexpectedDatatypeError;
            lulaError = std::move(createError);
            return Result::ERROR; //add new error type for unexpected data type
        }
        if (*(bool*)output.getData()) {
            if (cond == Conditional::IF) {
                scopeManager.increaseIndentationLevel();
            }
            if (cond == Conditional::WHILE) {
                scopeManager.increaseIndentationLevel(currentLine);
            }
            currentLine++;
            return Result::SUCCESS;
        }
        gotoEndOfScope();


    }
        break;
    case Key::CURLYBRACKET: {
        if (tokens.getSize() != 1) {
            return Result::SYNTAXERROR;
        }
        uint32_t newLine = scopeManager.lowerIdentationLevel();
        if (newLine == 0) {
            currentLine++;
            return Result::SUCCESS;
        }
        currentLine = newLine;
        return Result::SUCCESS;
    }
        break;
        //a function is beginning on this line#
        //Beginning with a datatypename is actually pretty irellevant
    case Key::DATATYPENAME: {
        TokenListElement* next = tokens.getCurrentElement().getNext();
        if (next->getToken().getKey() != Key::FUNCTIONNAME) {
            return Result::ERROR; //IMPROVE THIS ERROR -> UnexpectedTokenError
        }
        Function function;
        function.setName(std::move(*(std::string*)next->getToken().getData()));
        std::vector<DataType> inputs = {};
        next = next->next;
        if (next == nullptr) {
            return Result::SYNTAXERROR;
        }
        //in case the function has no parameters
        if (next->getToken().getKey() == Key::BRACKET) {
            if (!(*(Bracket*)next->getToken().getData() == Bracket::CLOSING)) {
                return Result::SYNTAXERROR; //make error better
            }
            next = next->next;
            goto parameterEnd; //program is able to add function without going through parameters
            
        }

        parameterReading: {
            TokenListElement* type = next;
            TokenListElement* name;
            TokenListElement* nextIndication;
            do {
                name = type->next;
                if (name == nullptr) {
                    return Result::SYNTAXERROR;
                }
                nextIndication = name->next;
                if (nextIndication == nullptr) {
                    return Result::SYNTAXERROR;
                }

                if (!(type->getToken().getKey() == Key::DATATYPENAME)) {
                    return Result::SYNTAXERROR;
                }
                inputs.push_back(*(DataType*)type->getToken().getData());
                if (!(name->getToken().getKey() == Key::VARIABLENAME)) {
                    return Result::SYNTAXERROR;
                }
                type = nextIndication->next;
                
            } while (nextIndication->getToken().getKey() == Key::SEPARATOR and *(Separator*)nextIndication->getToken().getData() == Separator::COMMA); //defererencing a non-Separator value as Separator is not harmful because Separator is primitive
            if (!(nextIndication->getToken().getKey() == Key::BRACKET)) {
                return Result::SYNTAXERROR;
            }
            if (!(*(Bracket*)nextIndication->getToken().getData() == Bracket::CLOSING)) {
                return Result::SYNTAXERROR;
            }
            next = nextIndication->next;
        }
        
        
        
        parameterEnd:
        if (next == nullptr) {
            return Result::SYNTAXERROR;
        }
        if (!(next->getToken().getKey() == Key::CURLYBRACKET)) {
            return Result::SYNTAXERROR;
        }
        if (!(*(Bracket*)next->getToken().getData() == Bracket::OPENING)) {
            return Result::SYNTAXERROR;
        }
        if (next->next != nullptr) {
            return Result::SYNTAXERROR;
        }
        function.setInputs(std::move(inputs));
        functionManager.addfunction(function.toSignature(), { "",currentLine });


        gotoEndOfScope();
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
        break;
    }

    return Result::SUCCESS;
}

Result LunarLangInterpreter::gotoEndOfScope() {
    uint32_t matchingCurlyBracketLine = findMatchingCurlyBracketLine(lines, currentLine + 1);
    if (matchingCurlyBracketLine == 0) {
        LulaErrorCreateObject createError;
        createError.errorMessage = "Unmatched bracket";
        createError.errorType = ErrorType::UnmatchedBracketError;
        lulaError = std::move(createError);
        return Result::ERROR; //add new error type for unexpected data type
    }
    TokenList checkList;
    checkList.fillFromLine(lines[matchingCurlyBracketLine]);
    if (checkList.getSize() != 1) {
        LulaErrorCreateObject createError;
        createError.errorMessage = "Unexpected token";
        createError.errorType = ErrorType::SyntaxError;
        lulaError = std::move(createError);
        return Result::ERROR; //add new error type for unexpected data type
    }
    if (checkList.getCurrentElement().getToken().getKey() != Key::CURLYBRACKET) {
        LulaErrorCreateObject createError;
        createError.errorMessage = "I seriously don't know";
        createError.errorType = ErrorType::NoError;
        lulaError = std::move(createError);
        return Result::ERROR; //add new error type for unexpected data type
    }
    if (*(Bracket*)checkList.getCurrentElement().getToken().getData() != Bracket::CLOSING) {
        LulaErrorCreateObject createError;
        createError.errorMessage = "I seriously don't know";
        createError.errorType = ErrorType::NoError;
        lulaError = std::move(createError);
        return Result::ERROR; //add new error type for unexpected data type
    }
    currentLine = matchingCurlyBracketLine + 1;
}
