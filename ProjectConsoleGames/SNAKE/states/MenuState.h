#pragma once

#include "../../CME/CME.h"
#include "IState.h"
#include "GameState.h"
#include "Menu.h"


class MenuState : public IState
{
public:
    MenuState() : menu_(std::make_unique<Menu>())
    {
        color_ = 1;
  
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

        menu_->AddItem(L"START");
        menu_->AddItem(L"TOP10");
        menu_->AddItem(L"QUIT");
    }

    void Update(StateManager& manager, float dt) override
    {
        color_ += 2 * dt;

        if (color_ > 2)
            color_ = 0;
    }

    void HandleInput(StateManager& manager, p_input& input) override
    {
        if (input->IsHitKey(CME::CONTROL::KEY_UP))
            menu_->Up();
        
        if (input->IsHitKey(CME::CONTROL::KEY_DOWN))
            menu_->Down();

        if (input->IsHitKey(CME::CONTROL::KEY_ENTER))
        {
            switch (menu_->CurrentSelect())
            {
            case(0):
                manager.ChangeState(std::make_unique<GameState>());
                break;
            case(1):
                ////change state to top10
                break;
            case(2):
                exit(0);
                break;
            }
        }
    }

    void Render(p_render& r) override
    {
        //change color
        if (color_ < 1)
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
        else if (color_ > 1)
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
        for (size_t i = 0; i < menu_->Size(); i++)
        {
            if (menu_->CurrentSelect() == i)
            {
                r->DrawString(22, 20 + i*2, menu_->Item(i), CME::COLOR::BLUE);
            }
            else
            {
                r->DrawString(22, 20 + i*2, menu_->Item(i), CME::COLOR::GREEN);
            }
        }
    }
private:
    std::vector<std::vector<int>> logo_;
    float color_;
    std::unique_ptr<Menu> menu_;
};