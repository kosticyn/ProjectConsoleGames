#pragma once

#include <Windows.h>
#include <bitset>
#include <vector>
#include <map>

namespace CME
{
    enum class CONTROL { KEY_MENU = 0, KEY_ENTER, KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN};

    class Input
    {
    public:
        Input()
        {
            table_keys_[CONTROL::KEY_MENU]  = VK_ESCAPE;
            table_keys_[CONTROL::KEY_ENTER]  = VK_RETURN;
            table_keys_[CONTROL::KEY_UP]    = VK_UP;
            table_keys_[CONTROL::KEY_DOWN]  = VK_DOWN;
            table_keys_[CONTROL::KEY_LEFT]  = VK_LEFT;
            table_keys_[CONTROL::KEY_RIGHT] = VK_RIGHT;
        }
        
        bool IsPressedKey(CONTROL key)
        {
            for (int i = 0; i < NUM_KEY; ++i)
            {
                keys_[i] = (0x8000 & GetAsyncKeyState(table_keys_[static_cast<CONTROL>(i)]));
            }

            return keys_[static_cast<int>(key)];
        }

    private:
       static constexpr size_t NUM_KEY = 6;
       std::bitset<NUM_KEY> keys_;
       std::map<CONTROL, int> table_keys_;
    };
}