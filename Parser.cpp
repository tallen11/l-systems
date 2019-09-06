//
// Created by Tate Allen on 9/5/19.
//

#include "Parser.h"

#include <sstream>
#include <iostream>

namespace lsys {

    Parser::Parser(const std::vector<Token> &tokens) : m_tokens(tokens), m_current(0) {

    }

    Parser::~Parser() {

    }

    void Parser::parse() {
        m_rules.clear();

        while (!isFinished()) {
            Token varToken = match(TokenType::Identifier);
            char varName = varToken.getLiteral().charValue;

            Rule* rule;
            if (m_rules.count(varName) == 0) {
                rule = new Rule();
                m_rules.insert(std::pair(varName, rule));
            } else {
                rule = m_rules[varName];
            }

            double probability = 1.0;
//            std::cout << peekCurrent().toString() << std::endl;
            if (peekCurrent().getType() == TokenType::OpenParen) {
                match(TokenType::OpenParen);
                Token probToken = match(TokenType::Number);
                match(TokenType::ClosedParen);

                probability = probToken.getLiteral().numberValue;
            }

            match(TokenType::Arrow);

            std::stringstream ss;
            while (m_current + 1 < m_tokens.size() && (m_tokens[m_current + 1].getType() == TokenType::Identifier || m_tokens[m_current+1].getType() == TokenType::Eof)) {
                ss << match(TokenType::Identifier).getLiteral().charValue;
            }

            rule->addBranch(RuleBranch(ss.str(), probability));
        }

        for (auto& pair : m_rules) {
            pair.second->prepare();
        }
    }

    Token Parser::match(TokenType type) {
        if (m_tokens[m_current].getType() == type) {
            m_current += 1;
            return m_tokens[m_current - 1];
        }

        std::stringstream ss;
        ss << "Unexpected token " << m_tokens[m_current].toString();
        throw ParseError(ss.str(), m_tokens[m_current].getLine());
    }

    Token Parser::peekCurrent() const {
        return m_tokens[m_current];
    }

    bool Parser::isFinished() const {
        return m_current >= m_tokens.size() || m_tokens[m_current].getType() == TokenType::Eof;
    }
}
