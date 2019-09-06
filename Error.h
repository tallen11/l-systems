//
// Created by Tate Allen on 9/6/19.
//

#ifndef L_SYSTEM_PARSER_ERROR_H
#define L_SYSTEM_PARSER_ERROR_H

#include <string>
#include <exception>
#include <optional>

namespace lsys {

    class Error : public std::exception {
    public:
        explicit Error(const std::string& message) : m_message(message) { }
        Error(const std::string& message, int line) : m_message(message), m_line(line) { }

        [[nodiscard]] std::string getMessage() const { return m_message; }
        [[nodiscard]] std::optional<int> getLine() const { return m_line; }

    private:
        std::string m_message;
        std::optional<int> m_line;
    };
}


#endif //L_SYSTEM_PARSER_ERROR_H
