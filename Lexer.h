//
// Created by Tate Allen on 9/5/19.
//

#ifndef L_SYSTEM_PARSER_LEXER_H
#define L_SYSTEM_PARSER_LEXER_H

#include <vector>

#include "Token.h"

namespace lsys {

    class LexError : public std::exception {
    public:
        LexError(const std::string &message, int line) : m_message(message), m_line(line) {}
        ~LexError() override = default;

    private:
        std::string m_message;
        int m_line;
    };

    class Lexer {
    public:
        explicit Lexer(const std::string &source);
        ~Lexer() = default;

        void lex();
        [[nodiscard]] std::vector<Token> getTokens() const { return m_tokens; }

    private:
        void lexSingleCharToken(TokenType type);
        void lexTwoCharToken(TokenType type, char first, char second);
        void lexIdentifier();
        void lexNumber();

        [[nodiscard]] bool isFinished() const;

        std::string m_source;
        std::vector<Token> m_tokens;
        int m_current;
        int m_line;
    };
}

#endif //L_SYSTEM_PARSER_LEXER_H
