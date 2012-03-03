#ifndef PERSON_H
#define PERSON_H

#include "building.h"
#include "math.h"
#include "entity.h"

//action


class PersonEvent {
    friend class Person;
public:
    enum PersonEventType {
        None,
        Move,
        Work,
        Rest,
        Shop
        //etc
    };

    PersonEvent();

    double getDuration() { return duration; }
    double evEnd() { return evStart + duration; }
    double getEvStart() { return evStart; }

    PersonEventType getPersonEventType() { return personEventType; }
    Building* getCurrentBuilding() { return currentBuilding; }
    Building* getDestination() { return destination; }

private:
    PersonEventType personEventType;
    double duration;
    //double _evEnd;
    double evStart;

    Building* currentBuilding;
    Building* destination; //only used for move-events
};


class Person : public Entity
{
public:
    Person();
    void processCurrentEvent();

    double getHealth() { return health; }
    double getSatiety() { return satiety; }
    double getCash() { return cash; }

    void finishCurrentAction();
    void createEvent();

    static double getMoveTime(Building* from, Building* to);
    double getMoveTime(Building* target);
private:

    //stats
    double health; //rest
    double satiety; //hunger/food
    double cash;

    //temp
    Building* workPlace;
    Building* localStore; //For now, only use one store
    Building* home;

    //action
    PersonEvent currentAction;
    std::list<PersonEvent*> pendingActions;
};

#endif // PERSON_H
