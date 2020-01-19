#pragma once

#include <string>
#include "IState.h"
#include "GameOver.h"
#include "../obj/Snake.h"
#include "../obj/Fruit.h"

class GameState : public IState
{
public:
    GameState() 
    {
        snake_ = std::make_unique<Snake>();
        fruit_ = std::make_unique<Fruit>();
        score_ = 0;
    }

    void Update(StateManager& manager, float dt) override
    {
        //Collision walls
        if (snake_->GetSnake().front().first < 0)
        {
            manager.ChangeState(std::make_unique<GameOver>()); 
            return;
        }

        if (snake_->GetSnake().front().first > 49)
        {
            manager.ChangeState(std::make_unique<GameOver>()); 
            return;
        }

        if (snake_->GetSnake().front().second < 0)
        {
            manager.ChangeState(std::make_unique<GameOver>());
            return;
        }

        if (snake_->GetSnake().front().second > 49)
        {
            manager.ChangeState(std::make_unique<GameOver>()); //changestate to gameover
            return;
        }

        //Collision tail
        auto head = snake_->GetSnake().front();
        
        int i = 0;
        for (auto& p : snake_->GetSnake())
        {
            
            if (i == 0)
            {
                i++;
                continue;
            }

            if (head == p)
            {
                manager.ChangeState(std::make_unique<GameOver>());
                return;
            }

            
        }
        
        score_ += snake_->Eat(fruit_);
        snake_->Update(dt);
        
    }

    void HandleInput(StateManager& manager, p_input& input) override
    {
        if (input->IsPressedKey(CME::CONTROL::KEY_UP))
        {
            snake_->MoveUP();
        }
        else
        if (input->IsPressedKey(CME::CONTROL::KEY_DOWN))
        {
            snake_->MoveDOWN();
        }
        else
        if (input->IsPressedKey(CME::CONTROL::KEY_LEFT))
        {
            snake_->MoveLEFT();
        }
        else
        if (input->IsPressedKey(CME::CONTROL::KEY_RIGHT))
        {
            snake_->MoveRIGHT();
        }

    }

    void Render(p_render& r) override
    {
        auto [fx, fy] = fruit_->Position();
        r->Draw(fx, fy, ' ', CME::COLOR::DARK_RED);

        for (auto p : snake_->GetSnake())
        {
            auto [sx, sy] = p;
            r->Draw(sx, sy, ' ', CME::COLOR::DARK_MAGENTA);
        }

        // score
        wchar_t s[256];
        swprintf_s(s, 256, L"Snake!          Score:  %i", score_, snake_->GetSnake().size());
        SetConsoleTitle(s);
    }


private:
    std::unique_ptr<Snake> snake_;
    std::unique_ptr<Fruit> fruit_;
    int score_;

};