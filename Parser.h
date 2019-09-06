//
// Created by Tate Allen on 9/5/19.
//

#ifndef L_SYSTEM_PARSER_PARSER_H
#define L_SYSTEM_PARSER_PARSER_H

#include <vector>
#include <unordered_map>
#include <memory>

#include "Token.h"
#include "Rule.h"
#include "Error.h"

namespace lsys {

    using RuleMap = std::unordered_map<char, std::shared_ptr<Rule>>;

    class Parser {
    public:
        explicit Parser(const std::vector<Token> &tokens);
        ~Parser();

        void parse();

        [[nodiscard]] RuleMap getRules() const { return m_rules; }

    private:
        Token match(TokenType type);

        [[nodiscard]] Token peekCurrent() const;
        [[nodiscard]] bool isFinished() const;

        std::vector<Token> m_tokens;
        int m_current;
        RuleMap m_rules;
    };
}

#endif //L_SYSTEM_PARSER_PARSER_H
