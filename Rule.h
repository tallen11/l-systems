//
// Created by Tate Allen on 9/5/19.
//

#ifndef L_SYSTEM_PARSER_RULE_H
#define L_SYSTEM_PARSER_RULE_H

#include <vector>
#include <algorithm>
#include <iostream>

namespace lsys {

    class RuleBranch {
    public:
        explicit RuleBranch(const std::string& production) : m_probability(1.0), m_production(production) { }
        RuleBranch(const std::string& production, double probability) : m_production(production), m_probability(probability) { }

        [[nodiscard]] double getProbability() const { return m_probability; }
        [[nodiscard]] std::string produce() const { return m_production; }

        void setProbability(double probability) { m_probability = probability; }

    private:
        double m_probability;
        std::string m_production;
    };

    class Rule {
    public:
        Rule() = default;
        ~Rule() = default;

        void addBranch(const RuleBranch& branch) {
            m_branches.push_back(branch);
        }

        void prepare() {
            if (m_branches.empty()) {
                return;
            }

            std::sort(std::begin(m_branches), std::end(m_branches), [](const RuleBranch& b1, const RuleBranch& b2) -> bool {
                return b1.getProbability() < b2.getProbability();
            });

            double sum = 0.0;
            for (auto& branch : m_branches) {
                sum += branch.getProbability();
                branch.setProbability(sum);
            }
        }

        [[nodiscard]] std::string produce() const {
            double low = m_branches[0].getProbability();
            double high = m_branches[m_branches.size() - 1].getProbability();
            double p = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / high));
            for (auto& branch : m_branches) {
                if (p <= branch.getProbability()) {
                    return branch.produce();
                }
            }

            return m_branches[m_branches.size() - 1].produce();
        }

        [[nodiscard]] std::string toString() const {
            std::stringstream ss;
            for (auto& branch : m_branches) {
                ss << "( " << branch.getProbability() << " ) -> " << branch.produce() << std::endl;
            }

            return ss.str();
        }

    private:
        std::vector<RuleBranch> m_branches;
    };
}

#endif //L_SYSTEM_PARSER_RULE_H
