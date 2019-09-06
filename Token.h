//
// Created by Tate Allen on 9/5/19.
//

#ifndef L_SYSTEM_PARSER_TOKEN_H
#define L_SYSTEM_PARSER_TOKEN_H

#include <string>
#include <sstream>

namespace lsys {

    enum class TokenType {
        Arrow, OpenParen, ClosedParen,
        Identifier,
        Number,
        Eof,
    };

    union TokenLiteral {
        static TokenLiteral identifier(char c) {
            TokenLiteral lit{};
            lit.charValue = c;
            return lit;
        }

        static TokenLiteral number(double d) {
            TokenLiteral lit{};
            lit.numberValue = d;
            return lit;
        }

        char charValue;
        double numberValue;
    };

    class Token {
    public:
        Token(TokenType type, int line) : m_type(type), m_line(line), m_literal({}) { }
        Token(TokenType type, TokenLiteral literal, int line) : m_type(type), m_literal(literal), m_line(line) { }
        ~Token() = default;

        [[nodiscard]] TokenType getType() const { return m_type; }
        [[nodiscard]] TokenLiteral getLiteral() const { return m_literal; }
        [[nodiscard]] int getLine() const { return m_line; }

        [[nodiscard]] std::string toString() const {
            switch (m_type) {
                case TokenType::Arrow: return "->";
                case TokenType::OpenParen: return "(";
                case TokenType::ClosedParen: return ")";
                case TokenType::Identifier: {
                    std::stringstream ss;
                    ss << '\'' << m_literal.charValue << '\'';
                    return ss.str();
                }
                case TokenType::Number: {
                    std::stringstream ss;
                    ss << m_literal.numberValue;
                    return ss.str();
                }
                case TokenType::Eof: return "EOF";
            }
        }

    private:
        TokenType m_type;
        TokenLiteral m_literal;
        int m_line;
    };
}

#endif //L_SYSTEM_PARSER_TOKEN_H
