#include "ASTNode.h"
#include <string>
#include <stdexcept>

int VariableDeclNode::interpret(Context& context)
{
	int val = value->interpret(context);
	context.setVariable(variableName, val);
	return val;
}

int IdentifierNode::interpret(Context& context)
{
	int val = value->interpret(context);
	return val;
}

int NumberNode::interpret(Context& context)
{
	return value;
}


int BinaryOpNode::interpret(Context& context)
{
	int leftVal = left->interpret(context);
	int rightVal = right->interpret(context);

	switch (op[0])
	{
	case '+':
		return leftVal + rightVal;
		break;
	case '-':
		return leftVal - rightVal;
		break;
	case '*':
		return leftVal * rightVal;
		break;
	case '/':
		if (rightVal == 0) {
			throw std::runtime_error("division by 0 error");
		}
		return leftVal / rightVal;
	default:
		throw std::runtime_error("unknown operator : " + op);
	}

}
