#include "Function.h"

void Function::setName(std::string&& name) {
    this->name = name;
}

void Function::setInputs(std::vector<DataType>&& inputs) {
    this->inputs = inputs;
}

std::string Function::toSignature() const {
    std::string uniqueReturnString = name;
    uniqueReturnString += (char)2;
    for (uint32_t i = 0; i < inputs.size(); i++) {
        switch (inputs[i])
        {
        case DataType::FLOAT:
            uniqueReturnString += 'f';
            break;
        case DataType::BOOL:
            uniqueReturnString += 'b';
            break;
        case DataType::STRING:
            uniqueReturnString += 's';
            break;
        }
    }
    uniqueReturnString += (char)3;
    return uniqueReturnString;
}
