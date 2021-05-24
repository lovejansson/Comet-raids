//
// Created by chasi127 on 2019-12-03.
//

#ifndef COMET_RAID_GAMESTATE_H
#define COMET_RAID_GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <utility>
#include <vector>

#include "State.h"
#include "DynamicObject.h"
#include "StaticObject.h"

class DynamicObject;
class StaticObject;

using dynamicObjPtr = std::shared_ptr<DynamicObject>;
using staticObjPtr = std::shared_ptr<StaticObject>;
using statePtr = std::shared_ptr<State>;

class GameState : public std::enable_shared_from_this<GameState>, public State {
public:
    GameState(int const currentLevel, sf::View & view);

    /**
     * Responsible creating an object of a certain type
     * type 0 = Ship1, type 1 = Ship 2, type 2 = IceBlock, type 3 = Comet, type 4 = BombSite
     * @param type type of object represented with an integer
     * @param position coordinates to where the object is to be placed
     */
    void createObject(int const type, sf::Vector2f const& position);

    /**
     * Adding a shared_pointer<DynamicObject> to the dynamicObjects vector
     * @param object shared_pointer<DynamicObject>
     */
    void addObject(dynamicObjPtr const object);

    /**
     * Adding a shared_pointer<StaticObject> to the staticObjects vector
     * @param object shared_pointer<StaticObject>
     */
    void addObject(staticObjPtr const object);

    /**
     * Removes objects from the  dynamicObjects and staticObjects
     * vectors that are marked to be removed i.e. alive == false.
     */
    void removeObjects();

    /**
     * Updates the game state
     * @param view sf::View is adjusted according to player movements.
     * @param quit bool if set to true the game ends.
     * @return returns shared_pointer to the new state to be run.
     */
    statePtr updateState(sf::View & view, bool & quit) override;

    /**
     * Renders the sprites and texts of the State.
     * @param drawTo sf::RenderWindow reference to draw to.
     */
    void renderState(sf::RenderWindow & drawTo) const override;

    /**
     * Sets the bool shipDied to true if the ship is dead.
     */
    void setShipDied();

    /**
     * Checks if the endTimer has run out.
     * @return true if endTimer is up.
     */
    bool checkTimeOut() const;

    /**
     * Adds one to the numbers of bombs placed in BombSites.
     */
    void addOneBombPlaced();

    /**
     * Calculates the size of the current level.
     * @return maximum x and y values of the level.
     */
    std::pair<float, float> getCometSize() const;

    /**
     * returns the endTimer as a sf::Text object.
     * @return sf::Text object.
     */
    sf::Text& getEndTimerText();

    /**
     * Adjusts the view to follow the player.
     * @param view The view to adjust.
     */
    void adjustView(sf::View & view) const;

private:
    /* Variables */
    /**
     * Keeps track of the elapsed time since first bomb has been placed in BombSite.
     */
    sf::Clock endTimer;

    /**
     * bool true if endTimer has been started else false.
     */
    bool endTimerStarted;

    /**
     * Text that shows endTimer countdown.
     */
    sf::Text endTimerText;

    /**
     * bool true if ship is alive else false.
     */
    bool shipDied;

    /**
     * Number of Bombs placed in BombSites.
     */
    int bombsPlaced;

    /**
     * Number of BombSites.
     */
    int totalSites;

    /**
     * The amount of time a player has to finish the level after
     * placing the first Bomb in a BombSite.
     */
    int currentEndTime;

    /**
     * Vector containing all DynamicObject type Objects in the game.
     */
    std::vector<dynamicObjPtr> dynamicObjects;

    /**
     * Vector containing all DynamicObject type Objects to be added to the game.
     */
    std::vector<dynamicObjPtr> dynamicAddList;

    /**
     * Vector containing all StaticObject type Objects in the game.
     */
    std::vector<staticObjPtr> staticObjects;

    /**
     * Vector containing all StaticObject type Objects to be added to the game.
     */
    std::vector<staticObjPtr> staticAddList;

    /* Functions */

    /**
     * Initializes the keys to be detected in GameState.update() and Ship.update().
     */
    void initializeKeys();

    /**
     * Initializes the text specific to this state to be rendered i.e. endTimerText.
     * @param view the current view to adjust text to.
     * @param text the text to be displayed.
     */
    void initializeText(sf::View & view, std::string const& text);

    /**
     * Initializes the IceBlocks of the level.
     */
    void initializeIceBlocks();

    /**
     * Checks that an object does not collide when created.
     * @param newObject The object to be added.
     * @return True if there is an collision else false.
     */
    bool startUpCollisions(dynamicObjPtr const& newObject) const;

    /**
     * Initializes the Objects of the Level.
     */
    void initializeObjects();

    /**
     * Main Initialize function, responsible for calling the other initialize functions.
     */
    void initializeGame();

    /**
     * Updates the Object lists
     */
    void updateObjectLists();

    /**
     * Updates any explosions currently running.
     */
    void updateExplosion() const;

    /**
     * Updates all DynamicObjects in the Level.
     * @param view Variable passed to functions further down in hierarchy.
     */
    void updateDynamicObjects(sf::View & view);

    /**
     * Checks collisions between DynamicObjects and StaticObjects.
     * @param view Variable passed to functions further down in hierarchy.
     */
    void collisionsWithStatic(sf::View & view);

    /**
     * Checks collisions between DynamicObjects and DynamicObjects.
     * @param view Variable passed to functions further down in hierarchy.
     */
    void collisionsWithDynamic(sf::View & view);

    /**
     * Searches for and returns pointer to a ship in the game.
     * @param shipId which ship to search for.
     * @return dynamicObjPtr Shared_Pointer<DynamicObject> to the ship
     */
    dynamicObjPtr getShip() const;

    /**
     * Checks if ship is left in the comet.
     * @return false if ship is in the comet, true otherwise.
     */
    bool shipLeftComet() const;

    /**
     * Checks if player(s) won the game.
     * @return true if win, false otherwise.
     */
    bool hasWon() const;

    /**
     * Checks if player(s) lost the game.
     * @return true if loss, false otherwise.
     */
    bool gameOver() const;
};

#endif //COMET_RAID_GAMESTATE_H
