#ifndef PARSER_HPP
#define PARSER_HPP

#include <Token.hpp>
#include <AST.hpp>

#include <vector>

class Parser {
    public:
        Parser();

        bool parse(const std::vector<Token>& tokens);

        ASTNode *getRoot();

        RuntimeContext buildRuntimeContext();

        void clear();
    private:    
        unsigned int m_ip;

        unsigned int m_errorTokenIndex;

        void advance();
        Token consume(TokenType type);
        Token peek(int offset = 0);
        Token currentToken();

        ASTNode* doFactor();
        ASTNode* doConjuction();
        ASTNode* doDisjunction();
        ASTNode* doImplication();
        ASTNode* doEquality(); //lol
        ASTNode* doExpression();

        std::vector<Token> m_tokens;

        ASTNode* m_astRoot;
        RuntimeContext m_runtimeContext;
};

#endif // PARSER_HPP
