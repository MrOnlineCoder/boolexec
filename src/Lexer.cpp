#include <Lexer.hpp>

#include <cstdlib>
#include <cstdio>
#include <iostream>

Lexer::Lexer() {
    m_tokens.reserve(1024);
}

bool Lexer::scan(const std::string& input) {

    std::size_t ip = 0;

    while (ip < input.length()) {
        char c = input[ip];

        if (isspace(c)) {
            ip++;
            continue;
        }

        if (isdigit(c)) {
           std::string digitStr;
           while (isdigit(c)) {
               digitStr += c;

               if (ip < input.length()) {
                   c = input[++ip];
               } else {
                   break;
               }
           } 

           int intVal = std::stoi(digitStr);
           m_tokens.push_back(Token(TokenType::CONST, intVal));
           continue;
        }

        if (c == '&') {
            m_tokens.push_back(Token(TokenType::OP_AND));
            ip++;
            continue;
        }

        if (c == '|') {
            m_tokens.push_back(Token(TokenType::OP_OR));
            ip++;
            continue;
        }

        if (c == '!') {
            m_tokens.push_back(Token(TokenType::OP_NOT));
            ip++;
            continue;
        }

        if (c == '(') {
            m_tokens.push_back(Token(TokenType::LPAREN));
            ip++;
            continue;
        }

        if (c == ')') {
            m_tokens.push_back(Token(TokenType::RPAREN));
            ip++;
            continue;
        }

        if (c == '=' && ip+1 < input.length() && input[ip+1] == '>') {
            m_tokens.push_back(Token(TokenType::OP_IMPLICATION));
            ip += 2;
            continue;
        }

        if (c == '<' && ip + 2 < input.length() && input[ip + 1] == '=' && input[ip + 2] == '>') {
            m_tokens.push_back(Token(TokenType::OP_EQ));
            ip += 3;
            continue;
        }

        if (isalpha(c)) {
            std::string id;
            while (ip < input.length() && !isspace(c) && (isalpha(c) || isdigit(c))) {
                id += c;
                c = input[++ip];
            }

            m_tokens.push_back(Token(TokenType::IDENTIFIER, id));
            continue;
        }

        return false;
    }

    return true;
}

const std::vector<Token>& Lexer ::getTokens() {
    return m_tokens;
}

void Lexer::dump() {
    for (auto token : m_tokens) {
        std::cout << "Token(" << static_cast<int>(token.getType()) << ", " << token.asInteger() << ", " << token.asString() << ")\n";
    }
}

void Lexer::clear() {
    m_tokens.clear();
}