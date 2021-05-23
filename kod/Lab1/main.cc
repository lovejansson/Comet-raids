#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "test");

    sf::CircleShape circle{100}; 
    circle.setOrigin(100, 100);
    circle.setPosition(512, 374);
    circle.setFillColor(sf::Color::Red);
  
    bool quit{false};
    bool upPressed = false;
    bool downPressed = false;
    bool leftPressed = false;
    bool rightPressed = false;

    while(!quit)
    {
        sf::Event event{};
        sf::Vector2f position{circle.getPosition()};
        while(window.pollEvent(event))
        {
            if (sf::Event::Closed)
            {
                quit = true; 
                break; 
            }
            else if( sf::Event::KeyPressed )
            {
                if(::sf::Keyboard::Q)
                {
                    quit = true;
                    break;
                }
                upPressed = true;
            }
            else if(sf::Event::KeyReleased)
            {
                upPressed = false;
            }
            
            if(upPressed)
            {
                circle.setPosition(position.x, position.y += 4);
            }
            std::cout << "Event: " << event.type << std::endl;
        }
        window.clear(sf::Color::White);
        window.draw(circle); 
        window.display();
    }
    return 0; 
}

