//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_DEFINITIONS_H
#define ASYLLUM_DEFINITIONS_H
#include <string>
#include <Windows.h>
class LolString
{
    char content[0x10]; // 0x0
    int len = 0; // 0x10
    int max = 0; // 0x14

public:

    operator const char* (void)
    {
        return c_str();
    }
    operator std::string(void)
    {
        return std::string(c_str());
    }

    std::string str()
    {
        return std::string(c_str());
    }

public:
    const char* c_str(void)
    {
        if (DWORD(this) <= 0x1000)
            return (const char*)"UNK";

        return *reinterpret_cast<const char**>(content);
    }
};
#endif //ASYLLUM_DEFINITIONS_H
