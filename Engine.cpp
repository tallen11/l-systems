//
// Created by Tate Allen on 9/6/19.
//

#include "Engine.h"

namespace lsys {

    Engine::Engine(const lsys::RuleMap &rules) : m_rules(rules) { }

    std::string Engine::expand(const std::string &str) const {
        std::stringstream ss;

        for (char c : str) {
            if (m_rules.count(c) == 0) {
                ss << c;
                continue;
            }

            std::shared_ptr<Rule> rule = m_rules.at(c);
            ss << rule->produce();
        }

        return ss.str();
    }
}
