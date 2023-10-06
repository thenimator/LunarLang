#include "defines.h"

OperationType getOperationType(Operator op) {
	switch (op)
	{
	case Operator::ADD:
		return OperationType::LINE;
		break;
	case Operator::SUBTRACT:
		return OperationType::LINE;
		break;
	case Operator::MULTIPLY:
		return OperationType::POINT;
		break;
	case Operator::DIVIDE:
		return OperationType::POINT;
		break;
	case Operator::EQUALS:
		return OperationType::EQUALS;
		break;
	case Operator::UNEQUALS:
		return OperationType::UNEQUALS;
		break;
	case Operator::AND:
		return OperationType::AND;
		break;
	case Operator::OR:
		return OperationType::OR;
		break;
	case Operator::LESSTHAN:
		return OperationType::COMPARISSON;
		break;
	case Operator::GREATERTHAN:
		return OperationType::COMPARISSON;
		break;
	case Operator::MODULO:
		return OperationType::MODULO;
		break;
	default:
		break;
	}
}

const char* operationString(Operator op) {
	switch (op)
	{
	case Operator::ASSIGN:
		return "=";
		break;
	case Operator::ADD:
		return "+";
		break;
	case Operator::SUBTRACT:
		return "-";
		break;
	case Operator::MULTIPLY:
		return "*";
		break;
	case Operator::DIVIDE:
		return "/";
		break;
	case Operator::OUTPUT:
		return "out";
		break;
	case Operator::EQUALS:
		return "==";
		break;
	case Operator::UNEQUALS:
		return "!=";
		break;
	case Operator::AND:
		return "and";
		break;
	case Operator::OR:
		return "or";
		break;
	default:
		break;
	}
}

const char* boolName(bool input) {
	if (input) {
		return "true";
	}
	return "false";
}