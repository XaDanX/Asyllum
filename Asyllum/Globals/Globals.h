//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_GLOBALS_H
#define ASYLLUM_GLOBALS_H

namespace Globals {
    extern int baseAddress;
    extern float viewMatrix[16];
    extern float projectionMatrix[16];
    extern float viewProjectionMatrix[16];
}
#define RVA(address) (Globals::baseAddress + (address))
#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}


#endif //ASYLLUM_GLOBALS_H
