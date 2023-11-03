#pragma once
#include "defines.h"
#include "Variable.h"

class Function {
public:
	void setName(std::string&& name);
	void setInputs(std::vector<DataType>&& inputs);
	Result call(const std::vector<Variable>& arguments);
	std::string toSignature() const;

private:
	std::string name;
	std::vector<DataType> inputs;
};

