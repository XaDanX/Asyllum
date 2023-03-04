//
// Created by XaDanX on 12/7/2022.
//

#ifndef ASYLLUM_CONSOLE_H
#define ASYLLUM_CONSOLE_H

#include <deque>
#include <string>
#include <Windows.h>

class Console {
public:
    void Render();

    void Show();

    void Hide();

    void Print(const char *fmt, ...);

private:
    bool ShowConsole = true;
    std::deque<std::string> consoleEvents;
};

#endif //ASYLLUM_CONSOLE_H
