#include "CME/CustomConsole/CustomConsole.h"
#include "CME/Render/Render.h"


using namespace CME;

int main()
{
    CustomConsole window(L"Custom console", 50, 50, 8);
    Render render(window.GetHandle());
    

    while(1)
    {
        render.Clear(COLOR::GREEN);   
        render.DrawRect(5, 5, 2, 3, COLOR::DARK_BLUE);
        render.Display();
    }
   
    
    
    return EXIT_SUCCESS;
}