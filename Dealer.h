#pragma once
#ifndef DEALER_H
#define DEALER_H

#include"User.h"
#include"Defines.h"

class Dealer: public User   {
public:

	Dealer(Deck* deck,int x,int y,int rot): User(deck,x,y,rot) {

	}

    void payOffAllWinners(const std::vector<std::shared_ptr<User>>& users) {
        printf("payed all winners\n");

        for (auto& user : users)
        {
            if (user == nullptr) { continue; }

            if (user->getScore() == 21 && this->_score != 21) {
                if(user->getStatus() == State::DOUBLE) { user->updare_balance(5); }
                user->updare_balance(2.5); 
            }
            else if(user->getStatus() == State::DOUBLE && user->getScore() < _score ){ user->updare_balance(4); }
            else if (user->getStatus() == State::CHECK && user->getScore() < _score) { user->updare_balance(2); }
            

            
        }
    }

    virtual void takeDecision (const std::vector<std::shared_ptr<User>>& users ) {
        while (_score < 17)
        {
            hit();
            this->deck_interface->pop_card();
        }
        if (_score > 21) {
            payOffAllWinners(users);
            return;
        }

        while (getLoseProb(users) > 0.5 && _score < 21)
        {
            hit();
            this->deck_interface->pop_card();
        }

        payOffAllWinners(users);
    
    }

    float getLoseProb(const std::vector<std::shared_ptr<User>>& users) {
        short higherScore = 0;
        short allPlayers = users.size() - 1;

        for (size_t i = 0; i < allPlayers; i++)
        {
            if (users[i]->getScore() > _score && users[i]->getScore() < 21) { higherScore++; }
        }
        return  (float)higherScore / allPlayers;
    }
     
    void flip_cards(bool face) {
        for (auto& card : my_cards)
        {
            card->flipCard(face);
        }
    }

    virtual State hit() override
    {
       

        if (my_cards.empty()) {
            this->my_cards.emplace_back(deck_interface->view_card());
        }
        else {
           // this->my_cards.emplace_back(deck_interface->view_card()->flipCard());
            // test case only 
            this->my_cards.emplace_back(deck_interface->view_card()->flipCard());
           
        }
        
        
        if (deck_interface->view_card()->get_symbol() == Symbols::ACE)
        {
            ++_aces;
            _score += 11;
        }
        else {
            _score += deck_interface->view_card()->get_card_val();
        }


        while (_score > 21 && _aces > 0) {
            _score -= 10; // Convert ace from 11 to 1
            _aces--;
        }

        std::cout << "dealer score: " << _score << "\n";
        

        return determine_status();
    }

     State determine_status() {
       // std::cout << "current score: " << _score << "\n";
        if (_score == 21) {
            _status = State::BLACKJACK;
        }
        else if (_score < 21) {
            _status = State::HIT;
        }
        else {
            _status = State::BUST;
        }
        return _status;
    }


     State check() override {
        if (_score == 0) {
            return State::NO_STATUS;
        }

        return _status = State::CHECK;
    }


    virtual State double_down() override { return (State)404; }
    
};


#endif // !DEALER_H
