#pragma once
#include <header/Core.h>
class Timer {
public:
    static void ClockBegin() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    static void ClockEnd() {
        end_time = std::chrono::high_resolution_clock::now();
    }

    static double GetMillisecondsDuration() {
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        return static_cast<double>(duration.count()) + (end_time - start_time - duration).count() / 1000000.0; // Converte a parte fracionária para milissegundos
    }

    static double GetSecondsDuration() {
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        return static_cast<double>(duration.count()) / 1000.0; // Converter para segundos
    }

private:
    static std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    static std::chrono::time_point<std::chrono::high_resolution_clock> end_time;
};

std::chrono::time_point<std::chrono::high_resolution_clock> Timer::start_time;
std::chrono::time_point<std::chrono::high_resolution_clock> Timer::end_time;