#ifndef LEXER_HPP
#define LEXER_HPP

#include <vector>

#include <Token.hpp>

class Lexer {
    public:
        Lexer();

        bool scan(const std::string& input);

        const std::vector<Token>& getTokens();

        void dump();

        void clear();
    private:
        std::vector<Token> m_tokens;
};

#endif // LEXER_HPP
