#pragma once
#include <memory>
#include "../CME/CME.h"

class IState;


class StateManager
{
public:
    StateManager();
    void Update(float dt);
    void InputHandle(std::unique_ptr<CME::Input>& input);
    void Render(std::unique_ptr<CME::Render>& render);
    void ChangeState(std::unique_ptr<IState> state);
private:
    std::unique_ptr<IState> state_;
};