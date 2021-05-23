#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
const size_t width = 1024;
const size_t height = 768;

int main()
{
	sf::RenderWindow window{sf::VideoMode{width, height}, "shoot"};

	sf::CircleShape circle{40};
	circle.setOrigin(40, 40);
	circle.setPosition(300, 300);
	circle.setFillColor(sf::Color::red);

	bool quit = false;
	while(!quit)
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					quit = true;
					break;
				default:
					cout << "Event: " << event.type << endl;
			}
		}
		window.draw(circle);
		window.display();
	}
	return 0;
}