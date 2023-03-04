//
// Created by XaDanX on 1/24/2023.
//

#ifndef ASYLLUM_EVENTMANAGER_H
#define ASYLLUM_EVENTMANAGER_H

#include <typeinfo>
#include <WTypesbase.h>
#include <unordered_map>

template<typename T>
constexpr static size_t GetHashCode() {
    return typeid(T).hash_code();
}

class EventManager {
private:
    std::unordered_map<size_t, std::vector<void *>> subscribers;
public:
    template<typename TEvent>
    inline constexpr void Subscribe(void *callback) {
        subscribers[GetHashCode<TEvent>()].emplace_back(callback);
    }

    template<typename TEvent>
    inline constexpr void Publish(TEvent event) {
        auto found = subscribers.find(GetHashCode<TEvent>());

        if (found == subscribers.end()) {
            return;
        }

        for (auto sub: found->second) {
            static_cast<void (*)(TEvent)>(sub)(event);
        }
    }

};


#endif //ASYLLUM_EVENTMANAGER_H
