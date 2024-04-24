#pragma once

#include <vector>
#include <memory>
#include "Card.h"

class BaseGameLogic
{
public:
    virtual State hit() = 0;
    virtual State check() = 0;
    virtual ~BaseGameLogic() = default;

protected:
    unsigned int _score = 0;
    unsigned int _second_score = 0;
    std::vector<std::shared_ptr<Card>> my_cards;
};
