#pragma once
#include <string>
#include <vector>

class Menu
{
public:
    Menu() : current_select_(0)
    {}

    void AddItem(std::wstring name)
    {
        items_.push_back(name);
    }

    int Size()
    {
        return items_.size();
    }

    int CurrentSelect()
    {
        return current_select_;
    }

    void CurrentSelect(int x)
    {
        current_select_ = x;
    }

    std::wstring Item(int i)
    {
        return items_[i];
    }

    void Up()
    {
        current_select_--;
        if (current_select_ < 0)
            current_select_ = items_.size() - 1;
    }

    void Down()
    {
        current_select_++;
        if (current_select_ > items_.size() - 1)
            current_select_ = 0;
    }

private:
    std::vector<std::wstring> items_;
    int current_select_;
};