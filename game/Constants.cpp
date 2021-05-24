//
// Created by chasi127 on 2019-12-15.
//

#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Constants.h"

/////////////////
// Constructor //
/////////////////

Constants::Constants()
:textureExplosion{}, textureIceBlock{}, textureShip{}, font{}, tickRate{120},
 levelTextures{}, bombSites{}, playerLocations{}, levelTimers{}
{
    /*Levels*/
    loadLevels();
    /* Object textures*/
    initializeTextures();
}

/////////////////////////////
// Public member functions //
/////////////////////////////

sf::Texture& Constants::getLevelTexture(int level)
{
    return levelTextures.at(level-1);
}

std::vector<sf::Vector2f>& Constants::getLevelBombSites(int level)
{
    return bombSites.at(level - 1);
}

std::vector<sf::Vector2f>& Constants::getPlayerLocation(int level)
{
    return playerLocations.at(level - 1);
}

int Constants::getLevelTimer(int level) const
{
    return levelTimers.at(level - 1);
}

int Constants::getNumberOfLevels() const
{
    return playerLocations.size();
}

//////////////////////////////
// Private member functions //
//////////////////////////////

void Constants::loadLevels()
{
    std::ifstream ifs{"textFiles/LEVELS.txt"};
    std::string line{};

    while(std::getline(ifs, line))
    {
        std::stringstream temp{line};

        if(temp.peek() == '/')
        {
            continue;
        }
        std::string tempAddress{};
        int tempEndTime{};
        std::vector<sf::Vector2f> tempCoordinates{};
        temp >> tempAddress;
        loadTexture(tempAddress);

        temp >> tempEndTime;
        levelTimers.push_back(tempEndTime);

        while(true)
        {
           float x{};
           float y {};
           temp >> x;
           if(temp.eof())
           {
               break;
           }
           temp >> y;
           sf::Vector2f coordinate{x, y};
           tempCoordinates.push_back(coordinate);
        }

        std::vector<sf::Vector2f> tempPlayerLocation{tempCoordinates.at(0)};
        playerLocations.push_back(tempPlayerLocation);

        std::vector<sf::Vector2f> tempBombSites{};
        std::copy(begin(tempCoordinates) + 1, end(tempCoordinates), std::back_inserter(tempBombSites));
        bombSites.push_back(tempBombSites);
    }
}

void Constants::loadTexture(std::string const& address)
{
    sf::Texture tempTexture{};
    tempTexture.loadFromFile(address);
    levelTextures.push_back(tempTexture);
}

void Constants::initializeTextures()
{
    /*Animations*/
    textureExplosion.loadFromFile("images/explosion_4.png");
    /*Static Textures*/
    textureIceBlock.loadFromFile("images/IceBlock_square.png");
    textureShip.loadFromFile("images/ship0.png");
    textureBomb.loadFromFile("images/bomb.png");
    textureProjectile.loadFromFile("images/bomb.png");
    textureBombSite.loadFromFile("images/bombSites.png");
    /*Fonts*/
    font.loadFromFile("images/INVASION2000.TTF");
}

Constants Constants::instance;




