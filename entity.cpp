#include "entity.h"
#include "entityevent.h"

#include <iostream>

Entity::Entity()
{
}

void Entity::processNextEvent()
{
    if(events.size() < 1) {
        std::cerr << "No events left!";
        return;
    }

    EntityEvent* entityEvent = events.front();
    std::cout << "Processing event " << entityEvent->type() << " " << entityEvent->time();
    events.pop_front();
    delete entityEvent;
}
