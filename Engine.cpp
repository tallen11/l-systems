//
// Created by Tate Allen on 9/6/19.
//

#include "Engine.h"

namespace lsys {

    Engine::Engine(const lsys::RuleMap &rules) : m_rules(rules) {

    }

    Engine::~Engine() {

    }

    std::string Engine::expand(const std::string &str) const {
        std::stringstream ss;

        for (char c : str) {

        }
    }
}
