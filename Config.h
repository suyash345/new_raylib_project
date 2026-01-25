#pragma once

#include <iostream>
#include "raylib.h"
#include <raymath.h>
#include <unordered_map>
#include <string>
#include <vector>



namespace Config{
    class Timer {
    public:
        Timer(double duration, bool repeat, bool auto_start) {

        }
        void Activate() {
            active = true;
            start_time = GetTime();
        }
        void Deactivate() {
        
        }

        void Update() {
            
        }

    private:
        double duration;
        bool repeat = false;
        bool auto_start = false;
        double  start_time;
        bool active = false;

    };


    inline constexpr Color BG_COLOR = {15,10,25,255};
	inline constexpr int WIDTH = 1920;
    inline constexpr int HEIGHT = 1080;
    inline constexpr float LASER_SPEED = 700;
} // namespace Config

		