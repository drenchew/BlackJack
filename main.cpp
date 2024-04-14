#include <SFML/Graphics.hpp>



#include<thread>
#include<mutex>

#include "Defines.h"
#include "Card.h"
#include"Deck.h"
#include"Background.h"


enum State
{
    HIT,
    CHECK,
    DOUBLE,
    SPLIT,

    BUST,
    SUCCESS,
    BLACKJACK,


    NO_STATUS=400,

};

class BaseGameLogic
{
public:
    virtual void hit() = 0;
    virtual void check() = 0;


    virtual ~BaseGameLogic() = default;

protected:
    unsigned int _score=0;
    unsigned int _second_score = 0;
    std::vector<std::shared_ptr<Card>> my_cards;
};

class Balance
{
public:
    void update_balance(const int bal) { _money = bal; }
    bool check_valid(const int b = 0) const { return (_money - b) >= 0; }
    

private:

    double _money = 100;
};

class Player final : public BaseGameLogic 
{
public:
    bool lock_actions = false;

    Player(Deck* deck) : deck_interface(deck), _status(State::NO_STATUS) { lock_actions = false; }

    virtual void hit() override final {
       
    }

   

    virtual void check() override
    {
        if (_score == 0) { return; }

        determine_status();
    }

    void double_down()
    {
        hit();
        if (_score < 21)
        {
            _status = State::DOUBLE;
        }
            
    }
    const State get_status() const
    {
        return this->_status;
    }

    

private:
    void determine_status()
    {
        std::cout << "current score: " << _score << "\n";

        if (_score == 21) { _status = State::BLACKJACK; }
        else if (_score < 21) { _status = State::SUCCESS; }
        else { _status = State::BUST;  }
    }
    
private:
    DeckInterface* deck_interface;
    State _status;
    Balance _balance;

    bool double_on_off = false;
    
};



int main()
{

   // srand(time(NULL));
    sf::RenderWindow window (sf::VideoMode(1024, 720), "SFML works!");
 
    Deck d;
    std::thread deck_thread(&Deck::generate_deck2, &d);

    Background bg;



    Player p1(&d);

    Player ppe(&d);
    Player pp(&d);
    std::vector<Player> players;
    players.emplace_back(p1);
    players.emplace_back(pp);

    for (auto& p : players)
    {
        std::cout << "player play\n";
        
        while (p.lock_actions != true)
        {
           
            std::cout << "player actions : " << p.lock_actions << "\n";
            int a;
            std::cin >> a;
            if (a == 1) { p1.check(); p.lock_actions = true;
            }
            if (a == 2) { p1.hit(); }
            if (a == 3) { p1.double_down(); }
        }

    }


    
    //sadjadhoa
   

    // Load image
    sf::Texture texture;
    if (!texture.loadFromFile("D:\\projects\\testSFML\\assets\\newCards\\test.png")) {
        // Error handling if the image fails to load
        return EXIT_FAILURE;
    }

    // Create sprite and set its texture
    sf::Sprite sprite;
    sprite.setRotation(59);
    sprite.setScale(0.75,0.75);
    sprite.setPosition(304,75);
    
    sprite.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                
                if(d.finished)
                    window.close();
            }
               
        }

        window.clear();
        // Draw sprite instead of shape

        bg.draw_background(window);
        
        window.draw(sprite);
       //c.draw_card(window);
        window.display();
    }

    deck_thread.join();
  

    return 0;
}
