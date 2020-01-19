#pragma once

#include <list>
#include <utility>
#include "Fruit.h"

using part = std::pair<short, short>;
enum class DIRECTION { UP = 0, DOWN, LEFT, RIGHT };

class Snake
{
public:
    Snake() 
    {
        //init snake
        snake_.push_back({ 25,25 });
        snake_.push_back({ 25,26 });
        snake_.push_back({ 25,27 });
        snake_.push_back({ 25,28 });
        DIR_ = DIRECTION::UP;
        speed_ = 20;
        step_ = 0;
    }

    void Update(float dt)
    {
        step_ += speed_ * dt;

        if (step_ > 1)
        {
            step_ = 0;

            auto head = snake_.front();
            snake_.pop_back();

            if (DIR_ == DIRECTION::UP)
            {
                head.second -= 1;
            }

            if (DIR_ == DIRECTION::DOWN)
            {
                head.second += 1;
            }

            if (DIR_ == DIRECTION::LEFT)
            {
                head.first -= 1;
            }

            if (DIR_ == DIRECTION::RIGHT)
            {
                head.first += 1;
            }

            snake_.push_front(head);
        }
    }

    void MoveUP()
    {
        if (DIR_ != DIRECTION::DOWN)
        {
            DIR_ = DIRECTION::UP;
        }
    }

    void MoveDOWN()
    {
        if (DIR_ != DIRECTION::UP)
        {
            DIR_ = DIRECTION::DOWN;
        }
    }

    void MoveLEFT()
    {
        if (DIR_ != DIRECTION::RIGHT)
        {
            DIR_ = DIRECTION::LEFT;
        }
    }

    void MoveRIGHT()
    {
        if (DIR_ != DIRECTION::LEFT)
        {
            DIR_ = DIRECTION::RIGHT;
        }
    }

    const std::list<part>& GetSnake() const
    {
        return snake_;
    }

    int Eat(std::unique_ptr<Fruit>& f)
    {
        if (snake_.front() == f->Position())
        {
            f->Position() = snake_.back();
            snake_.push_back(f->Position());

            bool available_position = false;
            int free = 0;

            while (!available_position)
            {
                f->Create();
                for (auto p : snake_)
                {
                    if (!(p == f->Position()))
                    {
                        free++;
                    }

                    if (free == snake_.size() - 1)
                    {
                        available_position = true;
                    }
                }
            }
            return 1;
        }

        return 0;
    }

private:
    std::list<part> snake_;
    DIRECTION DIR_;
    int speed_;
    float step_;

};