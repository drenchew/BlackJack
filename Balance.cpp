#include "Balance.h"

void Balance::update_balance(const int bal) {
    _money = bal;
}

bool Balance::check_valid(const int b) const {
    return (_money - b) >= 0;
}
