#include "CME/CustomConsole.h"
#include "CME/Render.h"
#include "CME/Input.h"
#include "CME/TimeStep.h"


using namespace CME;

struct Entity
{
    float pos_x = 10;
    float pos_y = 10;
    int speed = 30;
} player;

int main()
{


    auto window = std::make_unique<CustomConsole>(L"Custom console", 50, 50, 8);
    auto render = std::make_unique<Render>(window->GetHandle());
    auto input = std::make_unique<Input>();
    auto timer = std::make_unique<TimeStep>();

    
    timer->Reset();
    
    while(1)
    {
        timer->Tick();
        timer->Reset();

        render->Clear(COLOR::GREEN);   

        //input
        if (input->IsPressedKey(CONTROL::KEY_LEFT))
            player.pos_x -= player.speed * timer->DeltaTime();
        if (input->IsPressedKey(CONTROL::KEY_UP))
            player.pos_y -= player.speed * timer->DeltaTime();
        if (input->IsPressedKey(CONTROL::KEY_RIGHT))
            player.pos_x += player.speed * timer->DeltaTime();
        if (input->IsPressedKey(CONTROL::KEY_DOWN))
            player.pos_y += player.speed * timer->DeltaTime();
        if (input->IsPressedKey(CONTROL::KEY_MENU))
            break;
        
        //render
        render->DrawRect(player.pos_x, player.pos_y, 2, 2, COLOR::DARK_BLUE);
        render->Display();
        
      
    }
    
    return EXIT_SUCCESS;
}