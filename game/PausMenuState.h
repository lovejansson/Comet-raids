//
// Created by chasi127 on 2019-12-17.
//

#ifndef COMET_RAID_PAUSMENUSTATE_H
#define COMET_RAID_PAUSMENUSTATE_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "MenuState.h"
#include "GameState.h"

using statePtr = std::shared_ptr<State>;

class PausMenuState : public MenuState{
public:
    PausMenuState(int const currentLevel, sf::View & view,  statePtr currentGameState);

    /**
     * Updates the state by listening for the state relevant Keys i.e. Escape and Enter.
     * If escape the Menu shifts to StartMenu
     * If enter the State shifts back to the current GameState.
     * @param view The view to be updated.
     * @param quit If set to true the game ends.
     * @return std::shared_ptr<State> to the new state to be run.
     */
    statePtr updateState(sf::View & view, bool & quit) override;

private:
    /**
     * std::shared_ptr<State> to the current GameState.
     */
    statePtr currentGameState;
};

#endif //COMET_RAID_PAUSMENUSTATE_H
