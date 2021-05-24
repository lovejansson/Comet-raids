//
// Created by chasi127 on 2019-12-15.
//

#include <SFML/Graphics.hpp>
#include <memory>

#include "WinState.h"
#include "Constants.h"
#include "GameState.h"

using statePtr = std::shared_ptr<State>;

///////////////////
// Constructor ///
//////////////////

WinState::WinState(int const currentLevel, sf::View &view)
: MenuState{currentLevel, view, "Du Vann!"}, finalWin{false}
{
    if(currentLevel == Constants::instance.getNumberOfLevels())
    {
        finalWin = true;
        initializeTextLocal(view, "Jorden har klarat sig!");
    } else{
        initializeTextLocal(view, "Du Vann! men det kommer fler Kometer som hotar jorden!");
    }
}

/////////////////////////////
// Public member functions //
/////////////////////////////

statePtr WinState::updateState(sf::View & view, bool & quit)
{
    if(keys.at(sf::Keyboard::Return)) {
        if (finalWin) {
            return std::make_shared<GameState>(1, view);
        } else {
            return std::make_shared<GameState>(currentLevel + 1, view);
        }
    }
    else if(keys.at(sf::Keyboard::Escape))
    {
        return std::make_shared<MenuState>(currentLevel, view, "Comet Raids");
    }

    return nullptr;
}

//////////////////////////////
// Private member functions //
//////////////////////////////

void WinState::initializeTextLocal(sf::View &view, const std::string &text)
{
    if(finalWin)
    {
        header.setFont(Constants::instance.font);
        header.setString(text );
        header.setCharacterSize(30);
        header.setPosition(view.getCenter().x, view.getCenter().y - 250);
        header.setOrigin(header.getLocalBounds().width/2, header.getLocalBounds().height/2);

        enterText.setFont(Constants::instance.font);
        enterText.setString("Starta om spelet med Enter");
        enterText.setCharacterSize(20);
        enterText.setPosition(view.getCenter().x, view.getCenter().y - 100);
        enterText.setOrigin(enterText.getLocalBounds().width/2, enterText.getLocalBounds().height/2);
    } else{
        header.setFont(Constants::instance.font);
        header.setString(text );
        header.setCharacterSize(30);
        header.setPosition(view.getCenter().x, view.getCenter().y - 250);
        header.setOrigin(header.getLocalBounds().width/2, header.getLocalBounds().height/2);

        enterText.setFont(Constants::instance.font);
        enterText.setString("Res vidare med Enter");
        enterText.setCharacterSize(20);
        enterText.setPosition(view.getCenter().x, view.getCenter().y - 100);
        enterText.setOrigin(enterText.getLocalBounds().width/2, enterText.getLocalBounds().height/2);
    }

    escapeText.setFont(Constants::instance.font);
    escapeText.setString("Avsluta spelet med Escape");
    escapeText.setCharacterSize(20);
    escapeText.setPosition(view.getCenter().x, view.getCenter().y - 50);
    escapeText.setOrigin(escapeText.getLocalBounds().width/2, escapeText.getLocalBounds().height/2);

}