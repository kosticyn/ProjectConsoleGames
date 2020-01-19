#include "GameOver.h"
#include "MenuState.h"
#include "Menu.h"

GameOver::GameOver() : menu_(std::make_unique<Menu>())
{
    text_game_ =
    {
        {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
        {1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0},
        {1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1},
    };

    text_over_ =
    {
        {0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0},
        {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1},
    };

    menu_->AddItem(L"YES");
    menu_->AddItem(L"NO");
}

void GameOver::Update(StateManager& manager, float dt)
{

}

void GameOver::HandleInput(StateManager& manager, p_input& input)
{
    if (input->IsHitKey(CME::CONTROL::KEY_LEFT))
        menu_->Up();

    if (input->IsHitKey(CME::CONTROL::KEY_RIGHT))
        menu_->Down();

    if (input->IsHitKey(CME::CONTROL::KEY_ENTER))
    {
        switch (menu_->CurrentSelect())
        {
        case(0):
            manager.ChangeState(std::make_unique<GameState>());
            break;
        case(1):
            manager.ChangeState(std::make_unique<MenuState>());
            break;
        }
    }

}

void GameOver::Render(p_render& r)
{
    for (auto i = 0; i < 7; ++i)
        for (auto j = 0; j < 23; j++)
        {
            if (text_game_[i][j] == 1)
                r->Draw(13 + j, 5 + i, ' ', CME::COLOR::RED);
        }

    for (auto i = 0; i < 7; ++i)
        for (auto j = 0; j < 23; j++)
        {
            if (text_over_[i][j] == 1)
                r->Draw(13 + j, 14 + i, ' ', CME::COLOR::RED);
        }

    r->DrawString(20, 23, L"TRY AGAIN?", CME::COLOR::GREEN);

    //menu
    for (size_t i = 0; i < menu_->Size(); i++)
    {
        if (menu_->CurrentSelect() == i)
        {
            r->DrawString(16 + i * 15, 24, menu_->Item(i), CME::COLOR::BLUE);
        }
        else
        {
            r->DrawString(16 + i * 15, 24, menu_->Item(i), CME::COLOR::GREEN);
        }
    }

}