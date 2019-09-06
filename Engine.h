//
// Created by Tate Allen on 9/6/19.
//

#ifndef L_SYSTEM_PARSER_ENGINE_H
#define L_SYSTEM_PARSER_ENGINE_H

#include "Parser.h"

namespace lsys {

    class Engine {
    public:
        explicit Engine(const RuleMap& rules);
        ~Engine();

        [[nodiscard]] std::string expand(const std::string& str) const;

    private:
        RuleMap m_rules;
    };
}

#endif //L_SYSTEM_PARSER_ENGINE_H
