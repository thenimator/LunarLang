#include "LulaError.h"

LulaError::LulaError() {
	errorType = ErrorType::NoError;
	errorLine = 0;
}

const std::string& LulaError::what() {
	return errorMessage;
}

LulaError& LulaError::operator=(LulaErrorCreateObject&& data) {
	errorType = data.errorType;
	errorLine = data.errorLine;
	errorFilename = std::move(data.errorFilename);
	errorMessage = std::move(data.errorMessage);


	return *this;
}
