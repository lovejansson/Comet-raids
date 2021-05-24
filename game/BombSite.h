//
// Created by chasi127 on 2019-12-12.
//

#ifndef COMET_RAID_BOMBSITE_H
#define COMET_RAID_BOMBSITE_H

#include <SFML/Graphics.hpp>

#include "StaticObject.h"
#include "GameState.h"

class BombSite : public StaticObject{
public:
    BombSite(sf::Vector2f const& position);
    void collisionUpdate(GameState & world);

private:
    bool bombPlaced;
};

#endif //COMET_RAID_BOMBSITE_H
