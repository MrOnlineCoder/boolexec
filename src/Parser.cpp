#include <Parser.hpp>
#include <iostream>

Parser::Parser() : m_astRoot(NULL) {
    clear();
}

bool Parser::parse(const std::vector<Token>& tokens) {
    m_tokens = tokens;

    m_astRoot = doExpression();

    return m_errorTokenIndex != 0;
}

ASTNode* Parser::getRoot() {
    return m_astRoot;
}

Token Parser::currentToken() {
    return m_tokens[m_ip];
}

void Parser::clear() {
    if (m_astRoot != NULL) delete m_astRoot;

    m_astRoot = new ASTNode();

    m_errorTokenIndex = 0;
    m_ip = 0;
    m_runtimeContext.clear();
}

Token Parser::consume(TokenType type) {
    auto token = m_tokens[m_ip];

    if (token.getType() != type) {
        m_errorTokenIndex = m_ip;
        return Token(TokenType::NONE);
    }

    return token;
}

void Parser::advance() {
    m_ip++;
}

RuntimeContext Parser::buildRuntimeContext() {
    return m_runtimeContext;
}

Token Parser::peek(int offset) {
    if (m_ip + offset >= m_tokens.size()) return Token(TokenType::NONE);
    return m_tokens[m_ip + offset];
}

ASTNode* Parser::doFactor() {
    auto tok = currentToken();

    if (tok.getType() == TokenType::CONST) {
        advance();
        return new ConstNode(tok.asInteger());
    }

    if (tok.getType() == TokenType::IDENTIFIER) {
        advance();

        m_runtimeContext.registerVariable(tok.asString());

        return new VariableNode(tok.asString());
    }

    if (tok.getType() == TokenType::OP_NOT) {
        advance();

        auto operand = doFactor();

        auto node = new UnaryOpNode(tok);

        node->addChild(operand);

        return node;
    }

    if (tok.getType() == TokenType::LPAREN) {
        advance();

        auto expr = doExpression();

        consume(TokenType::RPAREN);

        return expr;
    }
}

ASTNode* Parser::doConjuction() {
    auto left = doFactor();

    while (peek().getType() == TokenType::OP_AND) {
        auto opToken = currentToken();
        advance();

        auto right = doFactor();

        auto node = new BinaryOpNode(opToken);

        node->addChild(left);
        node->addChild(right);

        left = node;
    }

    return left;
}

ASTNode* Parser::doDisjunction() {
    auto left = doConjuction();

    while (peek().getType() == TokenType::OP_OR) {
        auto opToken = currentToken();
        advance();

        auto right = doConjuction();

        auto node = new BinaryOpNode(opToken);

        node->addChild(left);
        node->addChild(right);

        left = node;
    }

    return left;
}

ASTNode* Parser::doExpression() {
    return doEquality();
}

ASTNode* Parser::doEquality() {
    auto left = doImplication();

    while (peek().getType() == TokenType::OP_EQ) {
        auto opToken = currentToken();
        advance();

        auto right = doImplication();

        auto node = new BinaryOpNode(opToken);

        node->addChild(left);
        node->addChild(right);

        left = node;
    }

    return left;
}

ASTNode* Parser::doImplication() {
    auto left = doDisjunction();

    while (peek().getType() == TokenType::OP_IMPLICATION) {
        auto opToken = currentToken();
        advance();

        auto right = doDisjunction();

        auto node = new BinaryOpNode(opToken);

        node->addChild(left);
        node->addChild(right);

        left = node;
    }

    return left;
}