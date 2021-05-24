//
// Created by chasi127 on 2019-12-03.
//

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <utility>
#include <vector>
#include <algorithm>
#include <random>

#include "GameState.h"
#include "MenuState.h"
#include "DynamicObject.h"
#include "StaticObject.h"
#include "Ship.h"
#include "IceBlock.h"
#include "Comet.h"
#include "Collision.h"
#include "Bomb.h"
#include "BombSite.h"
#include "Explosion.h"
#include "WinState.h"
#include "Constants.h"
#include "Projectile.h"
#include "PausMenuState.h"

using dynamicObjPtr = std::shared_ptr<DynamicObject>;
using staticObjPtr = std::shared_ptr<StaticObject>;
using statePtr = std::shared_ptr<State>;

///////////////////
// Constructor ///
//////////////////

GameState::GameState(int const currentLevel, sf::View & view)
: State{currentLevel}, endTimer{}, endTimerStarted{false}, endTimerText{}, shipDied{false}, bombsPlaced{}, totalSites{},
currentEndTime{}, dynamicObjects{}, dynamicAddList{}, staticObjects{}, staticAddList{}
{

    totalSites = Constants::instance.getLevelBombSites(currentLevel).size();
    currentEndTime = Constants::instance.getLevelTimer(currentLevel);
    initializeText(view, "Tid kvar: " + std::to_string(currentEndTime));
    initializeGame();
    adjustView(view);
}

/////////////////////////////
// Public member functions //
/////////////////////////////

void GameState::createObject(int const type, sf::Vector2f const& position)
{
    /* type 0 = Ship1, type 1 = IceBlock, type 2 = Comet, type 3 = BombSite */

    dynamicObjPtr tempDynamic{};
    staticObjPtr tempStatic{};

    switch(type){
        case 0:
            tempDynamic = dynamicObjPtr {new Ship{position}};
            addObject(tempDynamic);
            break;
        case 1:
            tempDynamic = dynamicObjPtr {new IceBlock{position}};
            if(!startUpCollisions(tempDynamic))
            {
                addObject(tempDynamic);
            }
            break;
        case 2:
            tempStatic = staticObjPtr {new Comet{currentLevel}};
            addObject(tempStatic);
            break;
        case 3:
            tempStatic = staticObjPtr {new BombSite{position}};
            addObject(tempStatic);
            break;
    }
}

void GameState::addObject(dynamicObjPtr const object)
{
    dynamicAddList.push_back(object);
}

void GameState::addObject(staticObjPtr const object)
{
    staticAddList.push_back(object);
}

void GameState::removeObjects()
{
    auto isDead = [](auto & object)
            {
                return !object->isAlive();
            };

    dynamicObjects.erase(remove_if(begin(dynamicObjects), end(dynamicObjects), isDead),
                  end(dynamicObjects));
    staticObjects.erase(remove_if(begin(staticObjects), end(staticObjects), isDead),
                        end(staticObjects));
}

statePtr GameState::updateState(sf::View & view, bool & quit)
{
    updateDynamicObjects(view);
    updateExplosion();
    collisionsWithDynamic(view);
    collisionsWithStatic(view);
    removeObjects();
    updateObjectLists();

    if(keys.at(sf::Keyboard::Escape))
    {

        keys.insert_or_assign(sf::Keyboard::Escape, false);
        return std::make_shared<PausMenuState>(currentLevel, view, shared_from_this());
    }
    /* Prevents player from droping to many Bombs and projectiles  */
    if(keys.at(sf::Keyboard::B))
    {
        keys.insert_or_assign(sf::Keyboard::B, false);
    }
    if(keys.at(sf::Keyboard::Space))
    {
        keys.insert_or_assign(sf::Keyboard::Space, false);
    }

    if(gameOver())
    {
        return std::make_shared<MenuState>(currentLevel, view, "Du Dog!");
    }

    if(hasWon())
    {
        /* TODO currentLevel++ when more levels exists */
        return std::make_shared<WinState>(currentLevel, view);
    }

    if(endTimerStarted)
    {
        endTimerText.setString(std::to_string(int(currentEndTime - endTimer.getElapsedTime().asSeconds())));
    }

    return nullptr;
}

void GameState::renderState(sf::RenderWindow & drawTo) const
{
    for(staticObjPtr staticObj : staticObjects)
    {
        staticObj->draw(drawTo);
    }

    for(dynamicObjPtr obj : dynamicObjects)
    {
        obj->draw(drawTo);
    }

    drawTo.draw(endTimerText);
    std::dynamic_pointer_cast<Ship>(getShip())->drawText(drawTo);
}

void GameState::setShipDied()
{
    shipDied = true;
}

bool GameState::checkTimeOut() const
{
    return endTimer.getElapsedTime().asSeconds() > currentEndTime && endTimerStarted;
}

void GameState::addOneBombPlaced()
{
    bombsPlaced++;
}

std::pair<float, float> GameState::getCometSize() const
{
    /* Returns iterator to the comet */
    auto cometItr{std::find_if(begin(staticObjects), end(staticObjects),
                               [](staticObjPtr obj){
                                   return std::dynamic_pointer_cast<Comet>(obj) != nullptr;
                               })};

    /* Gets maximum values of comets width and height */

    float cometHeight{};
    cometHeight = (*cometItr)->getSprite().getTexture()->getSize().y;

    float cometWidth{};
    cometWidth = (*cometItr)->getSprite().getTexture()->getSize().x;

    return std::make_pair(cometWidth, cometHeight);
}

sf::Text& GameState::getEndTimerText()
{
    return endTimerText;
}

void GameState::adjustView(sf::View & view) const
{
    sf::Sprite sprite1{getShip()->getSprite()};

    view.setCenter(sf::Vector2f(sprite1.getPosition().x, sprite1.getPosition().y));
    view.setSize( sf::Vector2f(792.f, 530.6f));
    view.setRotation(sprite1.getRotation());
}

//////////////////////////////
// Private member functions //
//////////////////////////////

void GameState::initializeKeys()
{
    keys.insert({sf::Keyboard::A, false});
    keys.insert({sf::Keyboard::D, false});
    keys.insert({sf::Keyboard::W, false});
    keys.insert({sf::Keyboard::S, false});
    keys.insert({sf::Keyboard::Q, false});
    keys.insert({sf::Keyboard::E, false});
    keys.insert({sf::Keyboard::B, false});
    keys.insert({sf::Keyboard::Space, false});
    keys.insert({sf::Keyboard::Escape, false});
}

void GameState::initializeText(sf::View & view, std::string const& text)
{
    endTimerText.setString(text);
    endTimerText.setCharacterSize(10);
    endTimerText.setFont(Constants::instance.font);
    endTimerText.setRotation(90);
    endTimerText.setOrigin(endTimerText.getLocalBounds().width/2,
                           endTimerText.getLocalBounds().height/2);
}

void GameState::initializeIceBlocks()
{
    std::random_device rand;
    std::mt19937 generator(rand());
    std::uniform_real_distribution<float> noise(-200, 200);
    unsigned int height{unsigned(getCometSize().first)};
    unsigned int width{unsigned(getCometSize().second)};
    for(unsigned int y{} ; y < height ; y += 250 )
    {
        for (unsigned int x{100}; x < width; x += 250)
        {
            float tempX{noise(generator) + x};
            float tempY{noise(generator) + y};
            createObject(1, sf::Vector2f{tempX, tempY});
        }
    }
}

bool GameState::startUpCollisions(dynamicObjPtr const& newObject) const
{
    for(auto obj1 : dynamicObjects)
    {
        if(Collision::PixelPerfectTest(newObject->getSprite(), obj1->getSprite()))
        {
            return true;
        }
    }
    for(auto obj2 : staticObjects)
    {
        return Collision::PixelPerfectTest(newObject->getSprite(), obj2->getSprite());
    }
}

void GameState::initializeObjects()
{
    /* Comet */
    createObject(2, {0, 0});

    /* Bombsites */
    for(int i{}; i < totalSites; ++i)
    {
        createObject(3, Constants::instance.getLevelBombSites(currentLevel).at(i));
    }

    /* Player(-s) */
    createObject(0, Constants::instance.getPlayerLocation(currentLevel).at(0));

    updateObjectLists();

    /* Ice blocks */
    initializeIceBlocks();

    updateObjectLists();
}

void GameState::initializeGame()
{
    initializeKeys();
    initializeObjects();
}

void GameState::updateObjectLists()
{
    if(staticAddList.size() >= 1)
    {
        std::copy(staticAddList.begin(), staticAddList.end(), std::back_inserter(staticObjects));
        staticAddList.clear();
    }
    if(dynamicAddList.size() >= 1)
    {
        std::copy(dynamicAddList.begin(), dynamicAddList.end(), std::back_inserter(dynamicObjects));
        dynamicAddList.clear();
    }
}

void GameState::updateExplosion() const
{
    for (auto staticObj : staticObjects) {
        if (staticObj != nullptr) {
            if (typeid(*staticObj) == typeid(Explosion)) {
                std::shared_ptr<Explosion> explosion{std::dynamic_pointer_cast<Explosion>(staticObj)};
                if (explosion->isAlive()) {
                    explosion->update();
                }
                explosion = nullptr;
            }
        }
    }
}

void GameState::updateDynamicObjects(sf::View & view)
{
    for(auto const& dynamicObj : dynamicObjects) {
        dynamicObj->update(view, *this);
    }
}

/* Checking collisions dynamic objects versus static objects */
void GameState::collisionsWithStatic(sf::View &view)
{
    for(auto dynamicObj : dynamicObjects)
    {
        for (auto staticObj : staticObjects)
        {
            if (Collision::PixelPerfectTest(dynamicObj->getSprite(), staticObj->getSprite(), 0))
            {
                /* Collision with the walls in the Comet */
                if (typeid(*staticObj) == typeid(Comet))
                {
                    dynamicObj->elasticCollision(staticObj, view, *this);
                }
                /* Collision with Explosion */
                else if (typeid(*staticObj) == typeid(Explosion))
                {
                    dynamicObj->collisionUpdate(*this);
                }

                /* If Bomb is placed on BombSite */
                else{
                    if(typeid(*dynamicObj) == typeid(Bomb) && dynamicObj -> getSpeed() < 50)
                    {
                        if(!endTimerStarted)
                        {
                            endTimer.restart();
                            endTimerStarted = true;
                        }
                        std::shared_ptr<BombSite> bombSitePtr{std::dynamic_pointer_cast<BombSite>(staticObj)};
                        std::shared_ptr<Bomb> bombPtr{std::dynamic_pointer_cast<Bomb>(dynamicObj)};
                        bombSitePtr->collisionUpdate(*this);
                        dynamicObj->setAliveStatus(false);
                    }
                }
            }
        }
    }
}

/* Checking collisions dynamic objects versus dynamic objects */
void GameState::collisionsWithDynamic(sf::View &view)
{
    auto itr {begin(dynamicObjects)};
    for(auto dynamicObj : dynamicObjects)
    {
        itr++;
        for (auto obj2{itr}; obj2 != end(dynamicObjects); ++obj2) {
            if (dynamicObj != (*obj2) && Collision::PixelPerfectTest(dynamicObj->getSprite(), (*obj2)->getSprite(), 0)) {

                /* Collisions between two ice blocks gives inelastic collision */
                std::shared_ptr iceBlockOne{std::dynamic_pointer_cast<IceBlock>(dynamicObj)};
                std::shared_ptr iceBlockTwo{std::dynamic_pointer_cast<IceBlock>((*obj2))};
                if (iceBlockOne != nullptr && iceBlockTwo != nullptr)
                {
                    if (iceBlockOne->getAge() < 10 && iceBlockTwo->getAge() < 10)
                    {
                        continue;
                    }
                    dynamicObjPtr newObject{dynamicObj->inelasticCollision((*obj2))};
                    if (newObject)
                    {
                        addObject(newObject);
                    }
                }
                /* Collisions between other dynamic objects gives elastic collisions */
                else{
                    std::shared_ptr iceBlockOne{std::dynamic_pointer_cast<IceBlock>(dynamicObj)};
                    std::shared_ptr ship{std::dynamic_pointer_cast<Ship>(dynamicObj)};
                    std::shared_ptr projectile{std::dynamic_pointer_cast<Projectile>(dynamicObj)};
                    dynamicObjPtr copy;
                    if (iceBlockOne)
                    {
                        copy = dynamicObjPtr{new IceBlock{*iceBlockOne}};
                        iceBlockOne = nullptr;
                    }
                    else if (ship)
                    {
                        copy = dynamicObjPtr{new Ship{*ship}};
                        ship = nullptr;
                    }
                    else if (projectile)
                    {
                        copy = dynamicObjPtr{new Projectile{*projectile}};
                        projectile = nullptr;
                    }
                    else{
                        std::shared_ptr bomb{std::dynamic_pointer_cast<Bomb>(dynamicObj)};
                        copy = dynamicObjPtr{new Bomb{*bomb}};
                        bomb = nullptr;
                    }
                    dynamicObj->elasticCollision((*obj2), view, *this);
                    (*obj2)->elasticCollision(copy, view, *this);
                    copy = nullptr;
                }
            }
        }
    }
}

dynamicObjPtr GameState::getShip() const
{
    auto shipItr{std::find_if(begin(dynamicObjects), end(dynamicObjects),
                              [](dynamicObjPtr obj) {
                                  auto temp{std::dynamic_pointer_cast<Ship>(obj)};
                                  return temp != nullptr;
                              })};
    return *shipItr;
}

bool GameState::shipLeftComet() const
{
    /* Gets maximum values of comets width and height */
    std::pair<float, float> cometSize{};
    cometSize = getCometSize();
    float cometHeight{};
    cometHeight = cometSize.second;
    float cometWidth{};
    cometWidth = cometSize.first;

    /* Get the position of the ship */
    sf::Vector2f shipPosition{};
    shipPosition = getShip()->getSprite().getPosition();

    /* Checks if Ship is outside the comet */
    if(shipPosition.x  >= cometWidth)
    {
        return true;
    }
    else if(shipPosition.x <= 0)
    {
        return true;
    }
    else if(shipPosition.y >= cometHeight)
    {
        return true;
    }
    else if(shipPosition.y <= 0)
    {
        return true;
    }

    return false;
}

bool GameState::hasWon() const
{
    return bombsPlaced == totalSites && shipLeftComet();
}

bool GameState::gameOver() const
{
    return checkTimeOut() || shipDied || (shipLeftComet() && bombsPlaced != totalSites);
}

