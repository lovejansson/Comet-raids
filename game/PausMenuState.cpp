//
// Created by chasi127 on 2019-12-17.
//

#include <SFML/Graphics.hpp>
#include <memory>
#include <utility>

#include "PausMenuState.h"
#include "GameState.h"

using statePtr = std::shared_ptr<State>;

/////////////////
// Constructor //
/////////////////

PausMenuState::PausMenuState(int const currentLevel, sf::View & view, statePtr currentGameState)
: MenuState{currentLevel, view, "             Paus!\n OBS Bombtimern Tickar!"}, currentGameState{std::move(currentGameState)}
{}

/////////////////////////////
// Public member functions //
/////////////////////////////

statePtr PausMenuState::updateState(sf::View & view, bool & quit)
{
   if(keys.at(sf::Keyboard::Return))
   {
       std::dynamic_pointer_cast<GameState>(currentGameState)->adjustView(view);
       return currentGameState;
   }
   else if(keys.at(sf::Keyboard::Escape))
   {
       return std::make_shared<MenuState>(currentLevel, view, "Comet Raids");
   }

   return nullptr;
}



