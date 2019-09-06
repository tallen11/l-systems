#include <iostream>
#include <fstream>

#include "Lexer.h"
#include "Parser.h"

int main() {
    std::ifstream file("../test/grammar.txt");
    if (!file.is_open()) {
        std::cout << "Failed opening file." << std::endl;
        return 1;
    }

    std::stringstream ss;

    std::string line;
    while (getline(file, line)) {
        ss << line << '\n';
    }

    file.close();

    lsys::Lexer lexer(ss.str());
    lexer.lex();

    auto tokens = lexer.getTokens();

    for (auto& t : tokens) {
        std::cout << t.toString() << " ";
    }
    std::cout << std::endl;

    lsys::Parser parser(tokens);
    try {
        parser.parse();
    } catch (const lsys::ParseError& error) {
        std::cout << "[Parser line " << error.getLine() << "]: " << error.getMessage();
        return 1;
    }

    auto rules = parser.getRules();
    for (auto& pair : rules) {
        std::cout << pair.first << std::endl;
        std::cout << pair.second->toString() << std::endl;
    }

    return 0;
}