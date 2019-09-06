#include <iostream>
#include <fstream>

#include "Util.h"
#include "Lexer.h"
#include "Parser.h"
#include "Engine.h"

void reportError(const lsys::Error& error, const std::string& grammarSource) {
    std::cout << "[Error]: " << error.getMessage() << std::endl;
    if (error.getLine() && error.getColumn()) {
        std::stringstream ss;
        ss << error.getLine().value() << ".";

        std::string lineNumberStr = ss.str();

        std::string line = split(grammarSource, '\n')[error.getLine().value()-1];
        std::cout << "\t" << lineNumberStr << "\t" << line << std::endl;
        std::cout << "\t";
        for (int i = 0; i < lineNumberStr.size(); ++i) {
            std::cout << " ";
        }

        std::cout << "\t";
        for (int i = 0; i < error.getColumn().value(); ++i) {
            std::cout << " ";
        }

        std::cout << "^ error location (" << error.getLine().value() << ", " << error.getColumn().value() << ")" << std::endl;
    }
}

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "Usage: lsys <grammar path> <iterations> <axiom>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
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

    int iterations = 0;
    try {
        iterations = std::stoi(argv[2]);
    } catch (...) {
        std::cout << "Failed parsing iterations. Please supply a positive integer." << std::endl;
        return 1;
    }

    lsys::Engine engine(parser.getRules());

    std::string result = std::string(argv[3]);
    for (int i = 0; i < iterations; ++i) {
        result = engine.expand(result);
    }

    std::cout << result << std::endl;

//    auto rules = parser.getRules();
//    for (auto& pair : rules) {
//        std::cout << pair.first << std::endl;
//        std::cout << pair.second->toString() << std::endl;
//    }

    return 0;
}