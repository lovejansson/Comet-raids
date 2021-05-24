//
// Created by chasi127 on 2019-12-03.
//

#ifndef COMET_RAID_STATE_H
#define COMET_RAID_STATE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>

class State;
using statePtr = std::shared_ptr<State>;

class State {
public:
    State(int const currentLevel);
    virtual ~State() = default;

    /**
     * Sets the key pressed to true in the keys map when that key is pressed.
     * @param key The variable in the map to be set true.
     */
    void onKeyPressed(sf::Keyboard::Key key);

    /**
     * Sets the key pressed to false in the keys map when that key is pressed.
     * @param key The variable in the map to be set false.
     */
    void onKeyReleased(sf::Keyboard::Key key);

    /**
     * Pure virtual method exact function varies between states.
     * @param view The view to be updated.
     * @param quit If update changes this variable to true the game ends.
     * @return shared_pointer<State> to the new state to be run.
     */
    virtual statePtr updateState(sf::View & view, bool & quit) = 0;

    /**
     * Pure virtual method. Renders the sprites and texts of the State.
     * @param drawTo sf::RenderWindow reference to draw to.
     */
    virtual void renderState(sf::RenderWindow & drawTo) const = 0;

    /**
     * Getter for the key map of the current state ( true or false ).
     * @return std::map<sf::Keyboard::Key, bool>.
     */
    std::map<sf::Keyboard::Key, bool> const& getKeys() const;

protected:

    /**
     * A map of keys the current state are listening to and their pressed status,
     * true if pressed else false.
     */
    std::map<sf::Keyboard::Key, bool> keys;

    /**
     * The current level of the game.
     */
    int currentLevel;
};

#endif //COMET_RAID_STATE_H
