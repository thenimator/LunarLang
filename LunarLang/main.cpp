#include "LunarLangInterpreter.h"
#include "LulaErrorAccess.h"
int main(int argc, char* argv[]) {
	LunarLangInterpreter interpreter;
	std::string input;
	if (argc == 1) {
		std::cout << argv[0] << "\n";
		std::cout << "Type the file path of the script you want to execute: " << "\n";
		std::cin >> input;
	}
	else if (argc == 2) {
		input = argv[1];
	}
	else {
		std::cout << "Not gonna deal with those arguments" << "\n";
		return -1;
	}
	
	Result result = interpreter.interpret(input.c_str());
	if (result != Result::SUCCESS) {
		std::cout << "SUCKS TO BE YOU!" << "\n";
		switch (result)
		{
		case Result::SYNTAXERROR:
			std::cout << "Syntax" << "\n";
			break;
		case Result::UNKNOWNVARIABLEERROR:
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
		std::cout << lulaError.what() << "\n";
		std::cout << "In " << lulaError.file() << "\n";
		std::cout << "On line " << lulaError.line() << "\n";
		return -1;
	}
	return 0;
}