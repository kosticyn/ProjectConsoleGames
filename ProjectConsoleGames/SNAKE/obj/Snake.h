#pragma once

#include <list>
#include <utility>



class Snake
{
public:
    Snake() 
    {
        snake_.push_back({ 25,25 });
        snake_.push_back({ 25,26 });
        snake_.push_back({ 25,27 });
        dir_ = UP;
        step_ = 0;
        alive_ = true;
    }

    const std::list<std::pair<short, short>>& GetSnake() const noexcept
    {
        return snake_;
    }

    void Move(float dt) noexcept
    {
        step_ += 1 * speed_ * dt;
        
        if (step_ > 1)
        {
            step_ = 0;
            auto front = snake_.front();
            snake_.pop_back();

            switch (dir_)
            {
            case(UP):
                front.second -= 1;
                break;
            case(DOWN):
                front.second += 1;
                break;
            case(LEFT):
                front.first -= 1;
                break;
            case(RIGHT):
                front.first += 1;
                break;
            default:
                break;
            }
            snake_.push_front(front);
        }
    }

    void DirUP() noexcept
    {
        if (dir_ !=DOWN)
            dir_ = UP;
    }

    void DirDOWN() noexcept
    {
        if (dir_ != UP)
            dir_ = DOWN;
    }

    void DirLEFT() noexcept
    {
        if (dir_ != RIGHT)
            dir_ = LEFT;
    }
    
    void DirRIGHT() noexcept
    {
        if (dir_ != LEFT)
            dir_ = RIGHT;
    }
    
    void IncSpeed() noexcept
    {
        speed_++;
    }

private:
    int speed_ = 10;
    std::list<std::pair<short, short>> snake_;
    enum direction { UP = 0, DOWN, LEFT, RIGHT } dir_;
    float step_;
    bool alive_;
};