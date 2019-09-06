//
// Created by Tate Allen on 9/6/19.
//

#ifndef L_SYSTEM_PARSER_UTIL_H
#define L_SYSTEM_PARSER_UTIL_H

#include <vector>
#include <sstream>

// https://stackoverflow.com/a/27511119
std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
         elems.push_back(std::move(item));
    }

    return elems;
}

#endif //L_SYSTEM_PARSER_UTIL_H
