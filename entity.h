#ifndef ENTITY_H
#define ENTITY_H

#include <list>

class EntityEvent;

class Entity
{
public:
    Entity();
    void processNextEvent();

private:
    std::list<EntityEvent*> events;

};

#endif // ENTITY_H
