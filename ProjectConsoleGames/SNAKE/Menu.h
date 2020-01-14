#pragma once

#include "../CME/CME.h"
#include "IState.h"

class Menu
{
public:
    Menu() : current_select_(0)
    {}
    
    void AddItem(std::wstring name)
    {
        items_.push_back(name);
    }

    int Size()
    {
        return items_.size();
    }

    int CurrentSelect()
    {
        return current_select_;
    }

    void CurrentSelect(int x)
    {
        current_select_ = x;
    }

    std::wstring Item(int i)
    {
        return items_[i];
    }

    void Up()
    {
        current_select_--;
        if (current_select_ < 0)
            current_select_ = items_.size() - 1;
    }

    void Down()
    {
        current_select_++;
        if (current_select_ > items_.size() - 1)
            current_select_ = 0;
    }

private:
    std::vector<std::wstring> items_;
    int current_select_;
};

class MenuState : public IState
{
public:
    MenuState()
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

        menu.AddItem(L"START");
        menu.AddItem(L"TOP10");
        menu.AddItem(L"QUIT");
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
            menu.Up();
        
        if (input->IsHitKey(CME::CONTROL::KEY_DOWN))
            menu.Down();

        if (input->IsHitKey(CME::CONTROL::KEY_ENTER))
        {
            switch (menu.CurrentSelect())
            {
            case(0):
                //change state to play game
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
        for (size_t i = 0; i < menu.Size(); i++)
        {
            if (menu.CurrentSelect() == i)
            {
                r->DrawString(22, 20 + i*2, menu.Item(i), CME::COLOR::BLUE);
            }
            else
            {
                r->DrawString(22, 20 + i*2, menu.Item(i), CME::COLOR::GREEN);
            }
        }
    }
private:
    std::vector<std::vector<int>> logo_;
    float color_;
    Menu menu;
};