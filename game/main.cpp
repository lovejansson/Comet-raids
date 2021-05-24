//
// Created by chasi127 on 2019-12-03.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include "State.h"

#include "GameState.h"
#include "DynamicObject.h"
#include "Ship.h"
#include "MenuState.h"
#include "Constants.h"

using namespace std;

using statePtr = std::shared_ptr<State>;


void run();

int main()
{
  run();
}

void run()
{
    sf::VideoMode desktop = sf::VideoMode().getDesktopMode();
    sf::RenderWindow window{desktop, "Comet Raids"};
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled (true);
    sf::View view(sf::Vector2f(792.f, 530.6f), sf::Vector2f(792.f, 530.6f));
    view.setRotation(0);
    window.setView(view);
    statePtr currentState{new MenuState{1, view, "Comet Raids"}};
    sf::Clock clock;

    long const microSeconds{1000000};
    long const mspt{microSeconds/Constants::instance.tickRate};

    sf::Time currentTime;
    sf::Time elapsedTime;
    sf::Time lastTimeStamp;
    long delta{};
    bool quit = false;

    while(!quit) {
        currentTime = clock.getElapsedTime();
        elapsedTime = currentTime - lastTimeStamp;
        lastTimeStamp = currentTime;
        delta += elapsedTime.asMicroseconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    quit = true;
                    break;
                case sf::Event::KeyPressed:
                    currentState->onKeyPressed(event.key.code);
                    break;
                case sf::Event::KeyReleased:
                    currentState->onKeyReleased(event.key.code);
                    break;
                default:
                    break;
            }
        }
        window.clear();
        if(delta >= mspt) {
            statePtr temp{};
            temp = currentState->updateState(view, quit);
            if(temp != nullptr)
            {
                currentState = temp;
            }
            delta = 0;
        }

        currentState->renderState(window);
        window.setView(view);
        window.display();
    }
}