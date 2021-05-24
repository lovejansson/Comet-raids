//
// Created by chasi127 on 2019-12-15.
//

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

#include "MenuState.h"
#include "GameState.h"
#include "Constants.h"

using statePtr = std::shared_ptr<State>;

/////////////////
// Constructor //
/////////////////

MenuState::MenuState(int const currentLevel, sf::View & view, std::string const& header)
:State{currentLevel}, header{}, enterText{}, escapeText{}
{
    adjustView(view);
    initializeText(view, header);
    initializeKeys();
}

/////////////////////////////
// Public member functions //
/////////////////////////////

statePtr MenuState::updateState(sf::View & view, bool & quit)
{
    if(keys.at(sf::Keyboard::Return))
    {
        return  std::make_shared<GameState>(currentLevel, view);
    }
    else if(keys.at(sf::Keyboard::Escape))
    {
        quit = true;
    }

    return nullptr;
}

void MenuState::renderState(sf::RenderWindow & drawTo) const
{
    drawTo.draw(header);
    drawTo.draw(enterText);
    drawTo.draw(escapeText);
}

//////////////////////////////
// Private member functions //
//////////////////////////////

void MenuState::adjustView(sf::View & view) const
{
    view.setRotation(0);
    view.setCenter(view.getSize().x, view.getSize().y);
}

void MenuState::initializeKeys()
{
    keys.insert({sf::Keyboard::Return, false});
    keys.insert({sf::Keyboard::Escape, false});
}

void MenuState::initializeText(sf::View & view, std::string const& text)
{
    header.setFont(Constants::instance.font);
    header.setString(text);
    header.setCharacterSize(30);
    header.setPosition(view.getCenter().x, view.getCenter().y - 250);
    header.setOrigin(header.getLocalBounds().width/2, header.getLocalBounds().height/2);

    enterText.setFont(Constants::instance.font);
    enterText.setString("Starta spelet med Enter");
    enterText.setCharacterSize(20);
    enterText.setPosition(view.getCenter().x, view.getCenter().y - 100);
    enterText.setOrigin(enterText.getLocalBounds().width/2, enterText.getLocalBounds().height/2);

    escapeText.setFont(Constants::instance.font);
    escapeText.setString("Avsluta spelet med Escape");
    escapeText.setCharacterSize(20);
    escapeText.setPosition(view.getCenter().x, view.getCenter().y - 50);
    escapeText.setOrigin(escapeText.getLocalBounds().width/2, escapeText.getLocalBounds().height/2);
}
