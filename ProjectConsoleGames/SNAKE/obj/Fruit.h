#pragma once

#include <utility>
#include <random>

class Fruit
{
public:
    Fruit()
    {
       Create();
    }

    void Create() noexcept
    {
        fruit_.first = Random();
        fruit_.second = Random();
    }

    std::pair<short, short>& Position() noexcept
    {
        return fruit_;
    }


private:
    short Random() noexcept
    {
        std::random_device rnd;
        std::mt19937 gen(rnd());
        std::uniform_int_distribution<short> uid(0, 49);
        return uid(gen);
    }

private:
    std::pair<short, short> fruit_;

};