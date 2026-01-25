#pragma once

#include <iostream>
#include "raylib.h"
#include <raymath.h>
#include <unordered_map>
#include <functional>
#include <string>
#include <vector>

class Timer {
public:
    Timer() {
    }
    Timer(double duration, bool repeat = false, bool auto_start = false, std::function<void()> callback = nullptr) : duration(duration), repeat(repeat),
        auto_start(auto_start), callback(callback) {
        if (auto_start) {
            Activate();
        }

    }
    void Activate() {
        active = true;
        start_time = GetTime();
    }
    void Deactivate() {
        active = false;
        start_time = 0;
        if (repeat) {
            Activate();
        }
    }

    void Update() {
        if (active) {
            if (GetTime() - start_time >= duration) {
                if (callback != nullptr && start_time != 0) {
                    callback();
                }
                Deactivate();
            }
        }
    }

private:
    double duration;
    bool repeat = false;
    bool auto_start = false;
    double  start_time;
    bool active = false;
    std::function<void()> callback;
};

namespace Config{
    inline constexpr Color BG_COLOR = {15,10,25,255};
	inline constexpr int WIDTH = 1920;
    inline constexpr int HEIGHT = 1080;
    inline constexpr float LASER_SPEED = 700;
    inline constexpr double METEOR_TIMER_DURATION = 0.4;
} // namespace Config

		