#include "LunarLangInterpreter.h"
int main() {
	LunarLangInterpreter interpreter;
	std::string input;
	std::cout << "Type the file path of the script you want to execute: " << "\n";
	std::cin >> input;
	Result result = interpreter.interpret(input.c_str());
	if (result != Result::SUCCESS)
		std::cout << "FUCK" << "\n";
}