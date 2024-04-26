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

inline void print(std::string& s) { std::cout << s << std::endl; }

void drawScreen(sf::RenderWindow& window,std::vector<Image>& imgs, std::vector<Player>& players)
{
    for (auto& img : imgs)
    {
        img.draw(window);
    }
    for (auto& player : players)
    {
        
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

    std::vector<Player> players;
    Player p1(&d,304,66,59);




   // bg.draw(window);

    // window.draw(sprite);
     //if (d.total_cards()) { 
    //  d.get_card()->draw_card(window);
    // }


    //std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Sleep for 2 seconds

   /* hit_btn.draw(window);
    check_btn.draw(window);
    double_btn.draw(window);

    window.display();*/

   
  // IMPLEMENT HIT FOR ACE WITH!

    players.emplace_back(p1);

    deck_thread.join();

    for (size_t i = 0; i < 5; i++)
    {
        window.clear();
        for (size_t i = 0; i < players.size(); ++i)
        {
            
            drawScreen(window,images,players);
            players[i].hit();
            players[i].drawHand(window);
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Sleep for 2 seconds
            players[i].deck_interface->pop_card();
        }

    }

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

                    // Check if the hit button is clicked
                    if (hit_btn.isClicked(mousePosition)) {
                        std::cout << "hit clicked\n";
                        p1.hit();
                        

                    }

                    // Check if the check button is clicked
                    else if (check_btn.isClicked(mousePosition)) {
                        std::cout << "check clicked\n";
                        p1.check();

                    }

                    // Check if the double button is clicked
                    else if (double_btn.isClicked(mousePosition)) {
                        std::cout << "double clicked\n";
                        p1.double_down();
                       
                    }

                    //std::cout << (int)p1.get_status()<< "\n";
//#define continue break
                    switch (p1.get_status())
                    {
                    case State::BUST: goto Busted;
                    case State::CHECK:  goto Busted;
                    case State::DOUBLE:  goto Busted;
                    }
                    p1.deck_interface->pop_card();
                   
                }
            }
               
        }

        window.clear();
       // // Draw sprite instead of shape
       // bg.draw(window);
       // 
       //// window.draw(sprite);
       // //if (d.total_cards()) { 
       ////  d.get_card()->draw_card(window);
       //// }
       //
       // 
       // std::this_thread::sleep_for(std::chrono::milliseconds(300)); // Sleep for 2 seconds

       // hit_btn.draw(window);
       // check_btn.draw(window);
       // double_btn.draw(window);
        drawScreen(window, images,players);

       //c.draw_card(window);
        window.display();
    }

Busted:
    window.clear();
    std::cout << "BUSTED\n";


 
   

    return 0;
}
