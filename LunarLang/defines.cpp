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
	default:
		break;
	}
}
