#include <SFML/Graphics.hpp>

#include<thread>
#include<mutex>
#include<chrono>
#include <exception>

#include "Defines.h"
#include "Card.h"
#include"Deck.h"
#include"Image.h"

#include"Player.h"
#include"Balance.h"

template<typename T>
inline void print(T s) { std::cout << s << std::endl; }

void drawScreen(sf::RenderWindow& window,std::vector<Image>& imgs, std::vector<Player*>& players)
{
    for (auto& img : imgs)
    {
        img.draw(window);
    }
    for (auto& player : players)
    {
        player->drawHand(window);
    }
}

void takeAction(BUTTON btn, std::vector<Player*> players)
{
    static volatile int playerNum = 0;
    if (playerNum > players.size()) { throw std::out_of_range("Index out of bounds!"); }
    switch (btn)
    {
    case BUTTON::HIT_BTN: players[playerNum]->hit();
        break;
    case BUTTON::CHECK_BTN: players[playerNum]->check(); playerNum++;
        break;
    case BUTTON::DOUBLE_BTN:  players[playerNum]->double_down(); playerNum++;
        break;
    case BUTTON::UNKNOWN: throw std::runtime_error("Something went wrong!");;
        break;
    }
}


int main()
{

   uint16_t constexpr SHIFT = 30;
  

   // srand(time(NULL));
    sf::RenderWindow window (sf::VideoMode(1024, 720), "SFML works!");
 
    Deck d;
    std::thread deck_thread(&Deck::generate_deck2, &d);

    Image bg(BUTTON::UNKNOWN,true);
    Image check_btn(BUTTON::CHECK_BTN);
    Image hit_btn(BUTTON::HIT_BTN);
    Image double_btn(BUTTON::DOUBLE_BTN);


    std::vector<Image> images;
    images.emplace_back(bg);
    images.emplace_back(check_btn);
    images.emplace_back(hit_btn);
    images.emplace_back(double_btn);

    std::vector<Player*> players;


    //Player p1(&d,304,66,59);
  //  Player* p1 = new Player(&d, 320, 66, 59);
 //  Player* p1 = new Player(&d, 320, 66, 50);
   std::shared_ptr<Player> p1(new Player(&d, 320, 66, 50));
   std::shared_ptr<Player> p2(new Player(&d, 490, 210, -10));
   std::shared_ptr<Player> p3(new Player(&d, 707, 137, -70));



  

    players.emplace_back(p1.get());
    players.emplace_back(p2.get());
    players.emplace_back(p3.get());

    deck_thread.join();

    for (size_t i = 0; i < 2; i++)
    {
       // window.clear();
        for (size_t i = 0; i < players.size(); ++i)
        {
            
            drawScreen(window,images,players);
            
            players[i]->hit();
            players[i]->drawHand(window);
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Sleep for 2 seconds

            players[i]->deck_interface->pop_card();
            print("TOTAL CARDS");
            print(p1->totalCards());
            print("\n");
        }

    }
    //print(p1.totalCards());
    std::cout << "AFTER FOR\n";
    

   

   
    bool isButtonClicked = false;


   
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

                  
                    if (hit_btn.isClicked(mousePosition)) {
                        std::cout << "hit clicked\n";
                       // p1->hit();
                        takeAction(BUTTON::HIT_BTN, players);

                       // p1.drawHand(window);
                      //  window.display();
                       // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                    }

                    // Check if the check button is clicked
                    else if (check_btn.isClicked(mousePosition)) {
                        std::cout << "check clicked\n";
                       // p1->check();
                       // 
                        takeAction(BUTTON::CHECK_BTN, players);
                      //  p1.drawHand(window);
                       // window.display();
                    }

                    // Check if the double button is clicked
                    else if (double_btn.isClicked(mousePosition)) {
                        std::cout << "double clicked\n";

                        takeAction(BUTTON::DOUBLE_BTN, players);
                       // p1->double_down();
                        //p1->drawHand(window);
                       // window.display();
                    }

                    //std::cout << (int)p1.get_status()<< "\n";

                    switch (p1->get_status())
                    {
                   // case State::BUST: std::this_thread::sleep_for(std::chrono::milliseconds(3000)); break;
                   // case State::CHECK: std::this_thread::sleep_for(std::chrono::milliseconds(3000)); break;
                   // case State::DOUBLE:  std::this_thread::sleep_for(std::chrono::milliseconds(3000)); break;
                    }
                    p1->deck_interface->pop_card();
                   
                }
            }
               
        }


       // window.clear();

       // std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Sleep for 2 seconds


        drawScreen(window, images,players);
        p1->drawHand(window);


        window.display();
    }

Busted:
    window.clear();
    std::cout << "BUSTED\n";

    //delete p1;

 
   

    return 0;
}
