#include <iostream>
#include <fstream>

#include "Util.h"
#include "Lexer.h"
#include "Parser.h"

void reportError(const lsys::Error& error, const std::string& grammarSource) {
    std::cout << "[Error]: " << error.getMessage() << std::endl;
    if (error.getLine()) {
        std::string line = split(grammarSource, '\n')[error.getLine().value()-1];
        std::cout << "\t" << error.getLine().value() << ".\t" << line << std::endl;
    }
}

int main(int argc, char** argv) {
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

    std::string grammarSource = ss.str();

    lsys::Lexer lexer(grammarSource);
    try {
        lexer.lex();
    } catch (const lsys::Error& error) {
        reportError(error, grammarSource);
        return 1;
    }

    auto tokens = lexer.getTokens();

    lsys::Parser parser(tokens);
    try {
        parser.parse();
    } catch (const lsys::Error& error) {
        reportError(error, grammarSource);
        return 1;
    }

    auto rules = parser.getRules();
    for (auto& pair : rules) {
        std::cout << pair.first << std::endl;
        std::cout << pair.second->toString() << std::endl;
    }

    return 0;
}