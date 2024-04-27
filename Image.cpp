#include "Defines.h"
#include "Image.h"

    
Image::Image(const BUTTON& btn,bool background) : _btn(btn) {

    std::string str = ".\\assets\\";


    constexpr int y_cords = 600;
    float scale_factor = 0.8f;

    if (background) {
        str += "background\\bgtable.jpg ";
        scale_factor = 1;
        goto ImageLoad;
        return;
    }

   
	switch (btn)
	{
    case BUTTON::CHECK_BTN: str += "btns\\checkbtn.png";
        _possition = sf::Vector2f(0, y_cords); break;
    case BUTTON::HIT_BTN: str += "btns\\hitbtn.png";
        _possition = sf::Vector2f(300, y_cords); break;
    case BUTTON::DOUBLE_BTN: str += "btns\\double.png";
        _possition = sf::Vector2f(600, y_cords); break;
    case BUTTON::UNKNOWN: return;
	}
    

    ImageLoad:
    try
    {
        this->bg_texture.loadFromFile(str); // .\\assets\\background\\bgtable.jpg 
        bg_sprite.setTexture(bg_texture);   // .\\assets\\btns\\hitbtn.png
        bg_sprite.setPosition(_possition);
        bg_sprite.setScale(scale_factor, scale_factor);
    }
    catch (const std::exception& e)
    {
        std::cerr << "failed to load image, reason: " << e.what() << "\n";
    }

}

void Image::draw(sf::RenderWindow& window) {
 //   std::cout << "drawing smth\n";
    window.draw(bg_sprite);
}

bool Image::isClicked(const sf::Vector2f& mousePosition) const {
    // Get the bounding box of the sprite
    sf::FloatRect bounds = bg_sprite.getGlobalBounds();
    // Check if the mouse position is within the bounding box
    return bounds.contains(mousePosition);
}
