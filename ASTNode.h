#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Context.h"

class ASTNode
{
public:
	virtual ~ASTNode() = default;
	virtual int interpret(Context& context) = 0;
};

class VariableDeclNode : public ASTNode {
	std::string variableName;
	std::unique_ptr<ASTNode> value;
public:
	VariableDeclNode(std::string name, std::unique_ptr<ASTNode> valueNode)
		: variableName(name), value(std::move(valueNode)) {}

	int interpret(Context& context) override;
};


class IdentifierNode : public ASTNode
{
	std::unique_ptr<ASTNode> value;
public:
	std::string name;
	IdentifierNode(const std::string& name) : name(name) {}
	int interpret(Context& context) override;

};

class NumberNode : public ASTNode
{
public:
	int value;
	NumberNode(int value) : value(value) {}
	int interpret(Context& context);
};



class BinaryOpNode : public ASTNode {
	std::unique_ptr<ASTNode> value;
public:
	std::string op;
	std::unique_ptr<ASTNode> left;
	std::unique_ptr<ASTNode> right;

	BinaryOpNode(const std::string& op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
		: op(op), left(std::move(left)), right(std::move(right)) {}
	int interpret(Context& context) override;
};

