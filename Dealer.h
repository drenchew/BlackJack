#pragma once
#ifndef DEALER_H
#define DEALER_H

#include"User.h"

class Dealer: public User   {
public:

	Dealer() {

	}
    virtual State hit() override
    {

    }
    virtual State check() override
    {

    }
    virtual const State getStatus() const override
    {

    }
    virtual void setStatus(const State state) override
    {

    }
    virtual void drawHand(sf::RenderWindow& window) override {

    }




};


#endif // !DEALER_H
