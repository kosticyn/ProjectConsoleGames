#pragma once
#include <chrono>

namespace CME
{
    class TimeStep
    {
    public:
        void Reset()
        {
            start_time_ = std::chrono::high_resolution_clock::now();
        }

        void Tick()
        {
            delta_time_ = std::chrono::high_resolution_clock::now() - start_time_;
        }

        float DeltaTime()
        {
            return delta_time_.count();
        }

    private:
        std::chrono::time_point<std::chrono::steady_clock> start_time_;
        std::chrono::duration<float> delta_time_;
        float time_scale_;
    };
}