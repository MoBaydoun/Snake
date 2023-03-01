#pragma once

class Game
{
public:
    static double deltaTime() {
        static auto last_time = std::chrono::high_resolution_clock::now();
        auto current_time = std::chrono::high_resolution_clock::now();
        double delta_time = std::chrono::duration<double>(current_time - last_time).count();
        last_time = current_time;
        return delta_time;
    }
private:
    Game() {}
};
