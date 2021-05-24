//
// Created by chasi127 on 2019-12-15.
//

#ifndef COMET_RAID_MENUSTATE_H
#define COMET_RAID_MENUSTATE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

#include "State.h"

using statePtr = std::shared_ptr<State>;

class MenuState : public State{
public:
    MenuState(int const currentLevel, sf::View & view, std::string const& header);

    /**
     * Updates the state by listening for the state relevant Keys i.e. Escape and Enter.
     * Exact behaviour depends on current MenuState but default is:
     * If Enter is pressed the game restarts at current level.
     * If Escape is pressed the game quits.
     * @param view The view to be updated.
     * @param quit If set to true the game ends.
     * @return std::shared_ptr<State> to the new state to be run.
     */
    virtual statePtr updateState(sf::View & view, bool & quit) override;

    /**
     * Renders the sprites and texts of the State.
     * @param drawTo sf::RenderWindow reference to draw to.
     */
    void renderState(sf::RenderWindow & drawTo) const override;

protected:
    /* Variables */

    /**
     * Header text of the menu.
     */
    sf::Text header;

    /**
     *Text that describes the result of pressing Enter.
     */
    sf::Text enterText;

    /**
     * Text that describes the effect of pressing escape.
     */
    sf::Text escapeText;

private:
    /* Functions */
    /**
     * Adjusts the view in the local menu by moving it and rotating it to 0.
     * @param view The view to be updated.
     */
    void adjustView(sf::View & view) const;

    /**
     * Initializes the keys the current state are listening to.
     */
    void initializeKeys();

    /**
     * Initializes the texts to be displayed in the current state.
     * @param view The view to be updated.
     * @param text The Header text of the State.
     */
    void initializeText(sf::View & view, std::string const& text);
};

#endif //COMET_RAID_MENUSTATE_H
