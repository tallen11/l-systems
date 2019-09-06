//
// Created by Tate Allen on 9/5/19.
//

#ifndef L_SYSTEM_PARSER_PARSER_H
#define L_SYSTEM_PARSER_PARSER_H

#include <vector>
#include <unordered_map>

#include "Token.h"
#include "Rule.h"

namespace lsys {

    class ParseError: std::exception {
    public:
        ParseError(const std::string& message, int line) : m_message(message), m_line(line) { }
        ~ParseError() override = default;

        [[nodiscard]] std::string getMessage() const { return m_message; }
        [[nodiscard]] int getLine() const { return m_line; }

    private:
        std::string m_message;
        int m_line;
    };

    class Parser {
    public:
        explicit Parser(const std::vector<Token> &tokens);
        ~Parser();

        void parse();

        [[nodiscard]] std::unordered_map<char, Rule*> getRules() const { return m_rules; }

    private:
        Token match(TokenType type);
        [[nodiscard]] Token peekCurrent() const;
        [[nodiscard]] bool isFinished() const;

        std::vector<Token> m_tokens;
        int m_current;
        std::unordered_map<char, Rule*> m_rules;
    };
}

#endif //L_SYSTEM_PARSER_PARSER_H
