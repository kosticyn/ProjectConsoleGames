#pragma once
#include <Windows.h>

namespace CME
{
    class CustomConsole
    {
    public:
        explicit CustomConsole() : handle_console_(GetStdHandle(STD_OUTPUT_HANDLE)) {}

        explicit CustomConsole(LPCTSTR title, short width, short height, short pixel_size) : 
            handle_console_(GetStdHandle(STD_OUTPUT_HANDLE))            
        {
            ConsoleTitle(title);
            ConsoleSize(width, height, pixel_size);
            CursorVisible(false);
        }

        void ConsoleTitle(LPCTSTR title)
        {
            SetConsoleTitle(title);
        }

        void ConsoleSize(short width, short height, short pixel_size)
        {
            width_ = width;
            height_ = height;

            SMALL_RECT window_size = { 0,0, 1, 1 };
            SetConsoleWindowInfo(handle_console_, TRUE, &window_size);

            COORD buffer_size = { width , height };
            SetConsoleScreenBufferSize(handle_console_, buffer_size);

            SetConsoleActiveScreenBuffer(handle_console_);

            FontSize(pixel_size, pixel_size);

            window_size = { 0,0, width - 1, height - 1 };
            SetConsoleWindowInfo(handle_console_, TRUE, &window_size);

            HWND hWnd;
            HMENU hm;
            hWnd = GetConsoleWindow();
            hm = GetSystemMenu(hWnd, FALSE);
            RemoveMenu(hm, SC_SIZE, MF_BYCOMMAND | MF_REMOVE);
            RemoveMenu(hm, SC_MAXIMIZE, MF_BYCOMMAND | MF_REMOVE);
            DrawMenuBar(hWnd);
        }

        void CursorVisible(bool b)
        {
            CONSOLE_CURSOR_INFO cursor_info;
            GetConsoleCursorInfo(handle_console_, &cursor_info);
            cursor_info.bVisible = b;
            SetConsoleCursorInfo(handle_console_, &cursor_info);
        }

        HANDLE GetHandle()
        {
            return handle_console_;
        }

        short GetWidth()
        {
            return width_;
        }

        short GetHeight()
        {
            return height_;
        }

        ~CustomConsole() { SetConsoleActiveScreenBuffer(handle_original_); }
    private:
        void FontSize(int x, int y)
        {
            CONSOLE_FONT_INFOEX font_info;
            font_info.cbSize = sizeof(font_info);
            font_info.nFont = 0;
            font_info.dwFontSize.X = x;
            font_info.dwFontSize.Y = y;
            font_info.FontFamily = FF_DONTCARE;
            font_info.FontWeight = FW_NORMAL;
            wcscpy_s(font_info.FaceName, L"Consolas");
            SetCurrentConsoleFontEx(handle_console_, FALSE, &font_info);
        }

    private:
        HANDLE handle_original_;
        HANDLE handle_console_;
        short width_;
        short height_;
    };
}