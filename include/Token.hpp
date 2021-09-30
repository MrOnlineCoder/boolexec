#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class TokenType {
    NONE = 0,
    CONST,
    OP_NOT,
    OP_AND,
    OP_OR,
    OP_IMPLICATION,
    OP_EQ,
    OP_XOR,
    OP_LOOP,
    LPAREN,
    RPAREN,
    IDENTIFIER
};

class Token {
    public:
        Token(TokenType type) : m_type(type), m_intValue(0) {

        };

        Token(TokenType type, std::string str) : m_type(type), m_strValue(str), m_intValue(0) {

        };

        Token(TokenType type, int num) : m_type(type), m_intValue(num), m_strValue(){

        };

        const TokenType getType() {
            return m_type;
        }

        const std::string& asString() {
            return m_strValue;
        }
        
        const int asInteger() {
            return m_intValue;
        }
    private:
        std::string m_strValue;
        int m_intValue;
        TokenType m_type;
};

#endif // TOKEN_HPP
