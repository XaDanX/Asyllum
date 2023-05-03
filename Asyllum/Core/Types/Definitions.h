//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_DEFINITIONS_H
#define ASYLLUM_DEFINITIONS_H

#include <string>
#include <Windows.h>

/*class LolString {
    char content[0x10]; // 0x0
    int len = 0; // 0x10
    int max = 0; // 0x14

public:

    operator const char *(void) {
        return c_str();
    }

    operator std::string(void) {
        return std::string(c_str());
    }

    std::string str() {
        return std::string(c_str());
    }

public:
    const char *c_str(void) {
        if (reinterpret_cast<uintptr_t>(this) <= 0x1000)
            return "UNK";

        return *reinterpret_cast<const char **>(content);
    }
};*/

class LolString {
    char content[0x20]; // 0x0
    int len = 0; // 0x20
    int max = 0; // 0x24

public:

    operator const char *(void) {
        return c_str();
    }

    operator std::string(void) {
        return std::string(c_str());
    }

    std::string str() {
        return std::string(c_str());
    }

public:
    const char *c_str(void) {
        if (reinterpret_cast<uintptr_t>(this) <= 0x1000)
            return "UNK";

        return max >= 0x10
               ? *reinterpret_cast<char**>(content)
               : content;
    }
};

#endif //ASYLLUM_DEFINITIONS_H
