//
// Created by love643 on 2019-12-11.
//

#ifndef COMET_RAID_STATICOBJECT_H
#define COMET_RAID_STATICOBJECT_H

#include <SFML/Graphics.hpp>
#include "Object.h"

/**
 * Interface class for all non moving objects.
 */
class StaticObject : public Object {
public:
    StaticObject(sf::Vector2f const& position);
    virtual ~StaticObject() = default;
};

#endif //COMET_RAID_STATICOBJECT_H
