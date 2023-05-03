//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_STRINGUTILS_H
#define ASYLLUM_STRINGUTILS_H

#include <string>
#include <algorithm>
#include <random>
#include "Windows.h"

inline namespace StringUtils {
    inline bool IsASCII(const char *buff, int maxSize) {
        for (int i = 0; i < maxSize; ++i) {
            if (buff[i] == 0)
                return true;
            if ((unsigned char) buff[i] > 127)
                return false;
        }
        return true;
    }

    inline std::string ToLower(std::string str) {
        std::string strLower;
        strLower.resize(str.size());

        std::transform(str.begin(),
                       str.end(),
                       strLower.begin(),
                       ::tolower);

        return strLower;
    }

    inline std::string RandomString(std::string::size_type length) {
        static auto &chrs = "0123456789"
                            "abcdefghijklmnopqrstuvwxyz"
                            "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        thread_local static std::mt19937 rg{std::random_device{}()};
        thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

        std::string s;

        s.reserve(length);

        while (length--)
            s += chrs[pick(rg)];

        return s;
    }

    inline std::string GetString(__int64 addr) {
        if (*(__int64 *) (addr + 0x10) > 15) {
            return std::string((char *) (*(__int64 *) addr));
        } else {
            return std::string((char *) addr);
        }
    }
}
#endif //ASYLLUM_STRINGUTILS_H
