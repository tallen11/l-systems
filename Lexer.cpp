//
// Created by Tate Allen on 9/5/19.
//

#include "Lexer.h"

namespace lsys {

    Lexer::Lexer(const std::string &source) :
            m_source(source),
            m_current(0),
            m_line(1) {}

    void Lexer::lex() {
        m_tokens.clear();

        while (!isFinished()) {
            char c = m_source[m_current];
            switch (c) {
                case '(': lexSingleCharToken(TokenType::OpenParen);break;
                case ')': lexSingleCharToken(TokenType::ClosedParen); break;

                case '-': lexTwoCharToken(TokenType::Arrow, '-', '>'); break;

                case ' ':
                case '\t':
                    m_current += 1;
                    break;
                case '\n':
                    m_line += 1;
                    m_current += 1;
                    break;

                default: {
                    if (isdigit(c)) {
                        lexNumber();
                    } else {
                        lexIdentifier();
                    }
                }
            }
        }

        m_tokens.emplace_back(TokenType::Eof, m_line);
    }

    void Lexer::lexSingleCharToken(TokenType type) {
        m_tokens.emplace_back(type, m_line);
        m_current += 1;
    }

    void Lexer::lexTwoCharToken(TokenType type, char first, char second) {
        if (m_current + 1 < m_source.size() && m_source[m_current + 1] == second) {
            m_tokens.emplace_back(type, m_line);
            m_current += 2;
        } else {
            std::stringstream ss;
            ss << "Expected '" << second << "' after '" << first << "'";
            throw LexError(ss.str(), m_line);
        }
    }

    void Lexer::lexIdentifier() {
        m_tokens.emplace_back(TokenType::Identifier, TokenLiteral::identifier(m_source[m_current]), m_line);
        m_current += 1;
    }

    void Lexer::lexNumber() {
        std::stringstream ss;
        char c = m_source[m_current];
        while (isdigit(c) || c == '.') {
            ss << c;
            m_current += 1;
            c = m_source[m_current];
        }

        try {
            double value = std::stod(ss.str());
            m_tokens.emplace_back(TokenType::Number, TokenLiteral::number(value), m_line);
        } catch (const std::invalid_argument& e) {
            throw LexError("Failed parsing invalid number", m_line);
        } catch (const std::out_of_range& e) {
            throw LexError("Parsed number was out of range", m_line);
        }
    }

    bool Lexer::isFinished() const {
        return m_current >= m_source.size();
    }
}
