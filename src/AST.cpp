#include <AST.hpp>

#include <iostream>
#include <cmath>

ASTNode::ASTNode() {
    m_children.reserve(2);

    
}

bool ASTNode::isLeafNode() {
    return m_children.size() == 0;
}

void ASTNode::addChild(ASTNode* node) {
    m_children.push_back(node);
}

ASTNode* ASTNode::getChild(int index) {
    return m_children[index];
}

const NodeType ASTNode::getType() {
    return NodeType::ROOT;
}

value_t ASTNode::eval(RuntimeContext& context) {
    return m_children[0]->eval(context);
}

ASTNode::~ASTNode() {
    for (auto node : m_children) {
        delete node;
    }
}

void ASTNode::dump(std::string prefix) {
    std::string node_type_str;

    if (getType() == NodeType::CONST) node_type_str = "Constant";
    if (getType() == NodeType::UNARY_OP) node_type_str = "UnaryOp";
    if (getType() == NodeType::BINARY_OP) node_type_str = "BinaryOp";
    if (getType() == NodeType::VARIABLE) node_type_str = "Variable";

    std::cout << prefix << "-> ASTNode(" << node_type_str << ")\n";

    for (auto child : m_children) {
        child->dump(prefix + "  ");
    } 
}

// ===============================
ConstNode::ConstNode(value_t v) {
    m_value = v;
}

const NodeType ConstNode::getType() {
    return NodeType::CONST;
}

value_t ConstNode::eval(RuntimeContext& context) {
    return m_value;
}

// ===============================
UnaryOpNode::UnaryOpNode(Token token) : m_token(token) {
}

const NodeType UnaryOpNode::getType() {
    return NodeType::UNARY_OP;
}

value_t UnaryOpNode::eval(RuntimeContext& context) {
    if (m_token.getType() == TokenType::OP_NOT) {
        return context.getK() - 1 - m_children[0]->eval(context);       
    }
}

// ===============================
BinaryOpNode::BinaryOpNode(Token token) : m_token(token) {
}

const NodeType BinaryOpNode::getType() {
    return NodeType::BINARY_OP;
}

value_t BinaryOpNode::eval(RuntimeContext& context) {
    auto left_value = m_children[0]->eval(context);
    auto right_value = m_children[1]->eval(context);

    switch (m_token.getType()) {
        case TokenType::OP_AND:
            return std::min(
                left_value,
                right_value
            );

        case TokenType::OP_OR:
            return std::max(
                left_value,
                right_value);

        case TokenType::OP_XOR:
            return left_value ^ right_value;

        case TokenType::OP_EQ:
            return left_value == right_value;

        case TokenType::OP_IMPLICATION:
            return left_value == 1 && right_value == 0 ? 0 : 1;
    }
}

// ===============================
VariableNode::VariableNode(std::string id) : m_name(id) {
}

const NodeType VariableNode::getType() {
    return NodeType::VARIABLE;
}

value_t VariableNode::eval(RuntimeContext& context) {
    return context.resolve(m_name);
}