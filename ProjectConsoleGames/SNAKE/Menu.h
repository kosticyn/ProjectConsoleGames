#pragma once

#include "../CME/CME.h"
#include "IState.h"

class Menu: public IState
{
public:
    Menu() 
    {
        color = 1;

        logo_ =
        {
            {0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0},
            {0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
            {1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1},
        };
    }

    void Update(StateManager& manager, float dt) override
    {
        color += 5 * dt;

        if (color > 2)
            color = 0;
    }
    void HandleInput(StateManager& manager, p_input& input) override
    {

    }

    void Render(p_render& r) override
    {
        //change color
        if (color < 1)
        {
            for (auto i = 0; i < 7; ++i)
            {
                for (auto j = 0; j < 29; ++j)
                {
                    if (logo_[i][j] == 1)
                        r->Draw(10 + j, 4 + i, ' ', CME::COLOR::BLUE);
                }
            }
            
        }
        else if (color > 1)
        {
            for (auto i = 0; i < 7; ++i)
            {
                for (auto j = 0; j < 29; ++j)
                {
                    if (logo_[i][j] == 1)
                        r->Draw(10 + j, 4 + i, ' ', CME::COLOR::RED);
                }
            }
            
        }

        //menu
        r->DrawString(22, 20, L"START", CME::COLOR::GREEN);
        r->DrawString(22, 22, L"RANK", CME::COLOR::GREEN);
        r->DrawString(22, 24, L"QUIT", CME::COLOR::GREEN);

    }

private:
    std::vector<std::vector<int>> logo_;
    float color;
};