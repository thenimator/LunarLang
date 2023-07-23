#pragma once
#include "defines.h"
#include "Token.h"

bool isConstant(Key key) {
	if (key == Key::INTCONSTANT)
		return true;
	if (key == Key::STRCONSTANT)
		return true;


	return false;
}