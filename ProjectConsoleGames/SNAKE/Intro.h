#pragma once

#include <vector>
#include "IState.h"
#include "Menu.h"


class Intro : public IState
{
public:
    Intro()
    {
        pos_x = 10;
        pos_y = 20;
        index = 0;
        

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

        if (index < 6)
            index += 10 * dt;

        if (index > 6)
            if (pos_y > 5)
                pos_y -= 15 * dt;

        if (pos_y < 5)
        {
            manager.ChangeState(std::make_unique<Menu>());
        }
    }

    void HandleInput(StateManager& manager, p_input& input) override
    {
        if (input->IsPressedKey(CME::CONTROL::KEY_ENTER))
        {
            manager.ChangeState(std::make_unique<Menu>());
        }
    }

    void Render(p_render& r) override
    {
        for (auto i = 0; i < index; ++i)
        {
            for (auto j = 0; j < 29; ++j)
            {
                if (logo_[i][j] == 1)
                    r->Draw(pos_x + j, pos_y + i, ' ', CME::COLOR::BLUE);
            }
        }
    }

private:
    std::vector<std::vector<int>> logo_;
    float index;
    float pos_x;
    float pos_y;
};
