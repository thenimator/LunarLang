#include "LunarLangInterpreter.h"
int main() {
	LunarLangInterpreter interpreter;
	std::string input;
	std::cout << "Type the file path of the script you want to execute: " << "\n";
	std::cin >> input;
	Result result = interpreter.interpret(input.c_str());
	if (result != Result::SUCCESS) {
		std::cout << "SUCKS TO BE YOU!" << "\n";
		switch (result)
		{
		case Result::SYNTAXERROR:
			std::cout << "Syntax" << "\n";
			break;
		case Result::UNKNOWNVARIABELERROR:
			std::cout << "Unknown variable" << "\n";
			break;
		case Result::ERROR:
			std::cout << "IDK you're screwed" << "\n";
			break;
		case Result::IMPLEMENTATIONERROR:
			std::cout << "NOOOOOOOOOOOOOOOOOOOOOOOOOO" << "\n";
			break;
		case Result::ILLEGALOPERATIONERROR:
			std::cout << "At least it narrows it down. Your code sucks" << "\n";
			break;
		default:
			break;
		}
	}
		
}