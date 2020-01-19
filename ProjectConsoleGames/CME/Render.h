#pragma once
#include <Windows.h>
#include <memory>
#include <string>

namespace CME
{
    namespace COLOR
    {
        enum COLORS : short
        {
            BLACK = 0,
            DARK_BLUE = 16,
            DARK_GREEN = 32,
            DARK_CYAN = 48,
            DARK_RED = 64,
            DARK_MAGENTA = 80,
            DARK_YELLOW = 96,
            GREY = 112,
            DARK_GREY = 128,
            BLUE = 144,
            GREEN = 160,
            CYAN = 176,
            RED = 192,
            MAGENTA = 208,
            YELLOW = 224,
            WHITE = 240,
        };
    }

    class Render
    {
    public:
        Render(HANDLE buffer) : handle_console_(buffer)
        {
            GetConsoleScreenBufferInfo(handle_console_, &buffer_info_);
            AttachBuffer(buffer);
        }

        void AttachBuffer(HANDLE buffer)
        {
            handle_console_ = buffer;
            width_ = buffer_info_.dwSize.X;
            height_ = buffer_info_.dwSize.Y;
            buffer_next_ = std::make_unique<CHAR_INFO[]>(width_ * height_);
        }

        void Clear(short color = 0)
        {
            for (short i = 0; i < width_ * height_; ++i)
            {
                buffer_next_[i].Char.UnicodeChar = ' ';
                buffer_next_[i].Attributes = color;
            }
        }

        void Draw(short x, short y, short ch, short color)
        {
            if (x >= 0 && x < width_ && y >= 0 && y < height_)
            {
                buffer_next_[y * width_ + x].Char.UnicodeChar = ch;
                buffer_next_[y * width_ + x].Attributes = color;
            }
        }

        void DrawRect(short x0, short y0, short x1, short y1, short color)
        {
            for (short x = x0; x < x1 + x0; ++x)
                for (short y = y0; y < y1 + y0; ++y)
                    Draw(x, y, ' ', color);

        }

        void DrawString(short x, short y, std::wstring s, short color)
        {
            for (short i = 0; i < s.size(); i++)
            {
                buffer_next_[y * width_ + x + i].Char.UnicodeChar = s[i];
                buffer_next_[y * width_ + x + i].Attributes = color;
            }
        }

        void Display()
        {
            WriteConsoleOutput(handle_console_, buffer_next_.get(), buffer_info_.dwSize, { 0, 0 }, &buffer_info_.srWindow);
        }

    private:
        HANDLE handle_console_;
        CONSOLE_SCREEN_BUFFER_INFO buffer_info_;
        std::unique_ptr<CHAR_INFO[]> buffer_next_;
        short width_;
        short height_;

    };
}