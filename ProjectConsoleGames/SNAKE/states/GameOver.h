#pragma once

#include "IState.h"

class Menu;

class GameOver : public IState
{
public:
    GameOver();

    void Update(StateManager& manager, float dt);

    void HandleInput(StateManager& manager, p_input& input);

    void Render(p_render& r);

private:
    std::vector<std::vector<int>> text_game_;
    std::vector<std::vector<int>> text_over_;
    std::unique_ptr<Menu> menu_;
};