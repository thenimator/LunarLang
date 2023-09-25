#include "LulaError.h"

LulaError::LulaError() {
	errorType = ErrorType::NoError;
	errorLine = 0;
}

const std::string& LulaError::what() {
	return errorMessage;
}

uint32_t LulaError::line() {
	return errorLine;
}

ErrorType LulaError::type() {
	return errorType;
}

const std::string& LulaError::file() {
	return errorFilename;
}

LulaError& LulaError::operator=(LulaErrorCreateObject&& data) {
	errorType = data.errorType;
	errorLine = data.errorLine;
	errorFilename = std::move(data.errorFilename);
	errorMessage = std::move(data.errorMessage);


	return *this;
}
