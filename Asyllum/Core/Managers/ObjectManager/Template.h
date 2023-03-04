//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_TEMPLATE_H
#define ASYLLUM_TEMPLATE_H

#include <vector>

class Template {
public:
    template<typename TType>
    static std::vector<TType> ReadTemplate(unsigned int address) {
        auto list = *reinterpret_cast<int *>(address);
        int template_array = *reinterpret_cast<int *>(list + 0x4);
        int template_array_length = *reinterpret_cast<int *>(list + 0x8);
        std::vector<TType> objectList;
        for (int index = 0; index < template_array_length; index++) {
            auto object = *reinterpret_cast<TType *>(template_array + (index * 4));
            objectList.push_back(object);
        }
        return objectList;
    }
};

#endif //ASYLLUM_TEMPLATE_H
