#pragma once
#include <memory>
#include "../CME/CME.h"

class IState;


class StateManager
{
public:
    StateManager();
    virtual void Update(float dt);
    virtual void InputHandle(std::unique_ptr<CME::Input>& input);
    virtual void Render(std::unique_ptr<CME::Render>& render);
    virtual void ChangeState(std::unique_ptr<IState> state);
private:
    std::unique_ptr<IState> state_;
};