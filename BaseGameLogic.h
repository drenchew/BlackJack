#pragma once

#include <vector>
#include <memory>
#include "Card.h"

class BaseGameLogic
{
public:
    virtual State hit() = 0;
    virtual State check() = 0;
    inline virtual int totalCards() { return this->my_cards.size(); }
    virtual const State get_status() const = 0;
    //virtual 
    virtual ~BaseGameLogic() = default;

    float _default_x = 0;
    float _default_y = 0;
protected:
   
    unsigned int _score = 0;
   // unsigned int _total_cards = 0;
    std::vector<std::shared_ptr<Card>> my_cards;
};
