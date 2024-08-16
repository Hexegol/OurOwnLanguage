#pragma once
#include <memory>
#include <string>
#include <vector>

class ASTNode
{
public:
	virtual ~ASTNode() = default;
};

class VariableDeclNode : public ASTNode {
public:
	std::string type;
	std::unique_ptr<ASTNode> identifier;
	std::unique_ptr<ASTNode> initializer; 

	VariableDeclNode(const std::string& type, std::unique_ptr<ASTNode> identifier)
		: type(type), identifier(std::move(identifier)) {}

	VariableDeclNode(const std::string& type, std::unique_ptr<ASTNode> identifier, std::unique_ptr<ASTNode> initializer)
		: type(type), identifier(std::move(identifier)), initializer(std::move(initializer)) {}
};


class IdentifierNode : public ASTNode
{
public:
	std::string name;
	IdentifierNode(const std::string& name) : name(name) {}
};

class NumberNode : public ASTNode
{
public:
	int value;
	NumberNode(int value) : value(value) {}
};



class BinaryOpNode : public ASTNode {
public:
	std::string op;
	std::unique_ptr<ASTNode> left;
	std::unique_ptr<ASTNode> right;

	BinaryOpNode(const std::string& op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
		: op(op), left(std::move(left)), right(std::move(right)) {}
};





