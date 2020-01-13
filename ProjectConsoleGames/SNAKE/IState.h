#pragma once

#include "../CME/CME.h"
#include "StateManager.h"

using p_input = std::unique_ptr<CME::Input>;
using p_render = std::unique_ptr<CME::Render>;
//using p_manager = std::unique_ptr<StateManager>;

class IState
{
public:
    virtual ~IState() = default;
    virtual void Update(StateManager& manager, float dt) = 0;
    virtual void HandleInput(StateManager& manager,p_input& input) = 0;
    virtual void Render(p_render& r) = 0;
};