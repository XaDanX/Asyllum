//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_TEMPLATE_H
#define ASYLLUM_TEMPLATE_H

#include <vector>

class Template {
public:
    template<typename TType>
    static std::vector<TType> ReadTemplate(uint64_t address) {
        uint64_t list = *reinterpret_cast<uint64_t*>(address);
        uint64_t template_array = *reinterpret_cast<uint64_t *>(list + 0x8);
        int template_array_length = *reinterpret_cast<int*>(list + 0x10);
        std::vector<TType> objectList;
        for (int index = 0; index < template_array_length; index++) {
            auto object = *reinterpret_cast<TType *>(template_array + (index * 8));
            objectList.push_back(object);
        }
        return objectList;
    }
};

#endif //ASYLLUM_TEMPLATE_H
