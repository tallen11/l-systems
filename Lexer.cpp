//
// Created by Tate Allen on 9/5/19.
//

#include "Lexer.h"

namespace lsys {

    Lexer::Lexer(const std::string &source) :
            m_source(source),
            m_current(0),
            m_line(1),
            m_column(0) { }

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
                    next(1);
                    break;
                case '\n':
                    m_line += 1;
                    m_column = 0;
                    next(1);
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

        m_tokens.emplace_back(TokenType::Eof, m_line, 0);
    }

    void Lexer::lexSingleCharToken(TokenType type) {
        m_tokens.emplace_back(type, m_line, m_column);
        next(1);
    }

    void Lexer::lexTwoCharToken(TokenType type, char first, char second) {
        if (m_current + 1 < m_source.size() && m_source[m_current + 1] == second) {
            m_tokens.emplace_back(type, m_line, m_column);
            next(2);
        } else {
            std::stringstream ss;
            ss << "Expected '" << second << "' after '" << first << "'";
            throw Error(ss.str(), m_line, m_column);
        }
    }

    void Lexer::lexIdentifier() {
        m_tokens.emplace_back(TokenType::Identifier, TokenLiteral::identifier(m_source[m_current]), m_line, m_column);
        next(1);
    }

    void Lexer::lexNumber() {
        std::stringstream ss;
        char c = m_source[m_current];
        while (isdigit(c) || c == '.') {
            ss << c;
            next(1);
            c = m_source[m_current];
        }

        try {
            double value = std::stod(ss.str());
            m_tokens.emplace_back(TokenType::Number, TokenLiteral::number(value), m_line, m_column);
        } catch (const std::invalid_argument& e) {
            throw Error("Failed parsing invalid number", m_line, m_column);
        } catch (const std::out_of_range& e) {
            throw Error("Parsed number was out of range", m_line, m_column);
        }
    }

    void Lexer::next(int amount) {
        m_current += amount;
        m_column += amount;
    }

    bool Lexer::isFinished() const {
        return m_current >= m_source.size();
    }
}
