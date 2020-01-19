#include "CME/CustomConsole.h"
#include "CME/Render.h"
#include "CME/Input.h"
#include "CME/TimeStep.h"
#include "SNAKE/states/IntroState.h"

#include "SNAKE/obj/snake.h"

using namespace CME;

struct Entity
{
    float pos_x = 10;
    float pos_y = 10;
    int speed = 30;
} player;

int main()
{
    auto window = std::make_unique<CustomConsole>(L"Snake!", 50, 50, 8);
    auto render = std::make_unique<Render>(window->GetHandle());
    auto input = std::make_unique<Input>();
    auto timer = std::make_unique<TimeStep>();
    auto manager = std::make_unique<StateManager>();
    
    timer->Reset();
    
    while(1)
    {
        timer->Tick();
        timer->Reset();

        render->Clear(COLOR::GREEN);   

        //input
        manager->InputHandle(input);

        //update
        manager->Update(timer->DeltaTime());

        //render
        manager->Render(render);
        render->Display();
    }
    
    return EXIT_SUCCESS;
}