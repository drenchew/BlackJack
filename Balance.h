#pragma once

class Balance
{
public:
    void update_balance(const int bal);
    bool check_valid(const int b = 0) const;

private:
    double _money = 100;
};
