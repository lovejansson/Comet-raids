//
// Created by chasi127 on 2019-12-15.
//

#ifndef COMET_RAID_WINSTATE_H
#define COMET_RAID_WINSTATE_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "MenuState.h"

using statePtr = std::shared_ptr<State>;

class WinState : public MenuState{
public:
    WinState(int const currentLevel, sf::View & view);

    /**
     * Updates the state by listening for the state relevant Keys i.e. Escape and Enter.
     * If escape the Menu shifts to StartMenu
     * If enter the State either shifts to the next level if there is one or restarts at level 1
     * @param view The view to be updated.
     * @param quit If set to true the game ends.
     * @return std::shared_ptr<State> to the new state to be run.
     */
    statePtr updateState(sf::View & view, bool & quit) override;

private:

    /**
    * If currentLevel is the last level finalWin is true else false this variable is used to change the Local texts
    * to reflect the correct WinState text.
    */
    bool finalWin;
     /**
      * A local variant of the InitializeText method to handle local non header texts.
      * @param view The view to be updated.
      * @param text Header text of the State.
      */
    void initializeTextLocal(sf::View &view, const std::string &text);
};

#endif //COMET_RAID_WINSTATE_H
