#include "StateManager.h"
#include "IState.h"
#include "IntroState.h"

StateManager::StateManager() : state_(std::make_unique<Intro>()) 
{}

void StateManager::Update(float dt)
{
    state_->Update(*this, dt);
}

void StateManager::InputHandle(std::unique_ptr<CME::Input>& input)
{
    state_->HandleInput(*this, input);
}

void StateManager::Render(std::unique_ptr<CME::Render>& render)
{
    state_->Render(render);
}

void StateManager::ChangeState(std::unique_ptr<IState> state)
{
    state_ = std::move(state);
}

