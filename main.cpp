#include <SFML/Graphics.hpp>



#include<thread>
#include<mutex>
#include<chrono>

#include "Defines.h"
#include "Card.h"
#include"Deck.h"
#include"Image.h"






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
   // d.generate_deck2();
    std::thread deck_thread(&Deck::generate_deck2, &d);

    Image bg(BUTTON::UNKNOWN,true);


   

    Player p1(&d);

    Player ppe(&d);
    Player pp(&d);
    std::vector<Player> players;
    players.emplace_back(p1);
    players.emplace_back(pp);

   /* for (auto& p : players)
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

    }*/


    //possition buttons
    Image check_btn(BUTTON::CHECK_BTN);
    Image hit_btn(BUTTON::HIT_BTN);
    Image double_btn(BUTTON::DOUBLE_BTN);

   
    // ".\\assets\\cards\\6_of_clubs.png"
    // Load image
    /*
    sf::Texture texture;
    if (!texture.loadFromFile(d.get_card()->get_path())) {
        // Error handling if the image fails to load
       //return EXIT_FAILURE;
    }

    // Create sprite and set its texture
    sf::Sprite sprite;
    sprite.setRotation(59);
    sprite.setScale(0.2,0.2);
    sprite.setPosition(304,75);
    
    sprite.setTexture(texture);
    */
    bool isButtonClicked = false;


    deck_thread.join();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                if (d.finished) { window.close();}
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    // Check if the hit button is clicked
                    if (hit_btn.isClicked(mousePosition)) {
                        std::cout << "hit clicked\n";
                        // Do something when the hit button is clicked
                    }

                    // Check if the check button is clicked
                    else if (check_btn.isClicked(mousePosition)) {
                        std::cout << "check clicked\n";
                        // Do something when the check button is clicked
                    }

                    // Check if the double button is clicked
                    else if (double_btn.isClicked(mousePosition)) {
                        std::cout << "double clicked\n";
                        // Do something when the double button is clicked
                    }
                   
                }
            }
               
        }

        window.clear();
        // Draw sprite instead of shape
        bg.draw(window);
        
       // window.draw(sprite);
        if (d.view_card()) { 
         d.get_card()->draw_card(window); }
       
        
        std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Sleep for 2 seconds

        hit_btn.draw(window);
        check_btn.draw(window);
        double_btn.draw(window);

       //c.draw_card(window);
        window.display();
    }

 
  

    return 0;
}
