#ifndef PERSON_H
#define PERSON_H

#include "building.h"
#include "math.h"

class Person
{
public:
    Person();
private:
    //stats
    double health; //rest
    double satiety; //hunger/food
    double cash;

    //pos
    //int x;
    //int y;

    Building* currentBuilding;
    Building* workPlace;
    Building* localStore; //For now, only use one store
    Building* home;

    //action
    enum PersonEvent {
        Move,
        Work,
        Rest,
        Shop
        //etc
    };
    double duration;
    double end; //time of completion
    PersonEvent personEvent;
    void processEvent();

    getMoveTime(Building* from, Building* to);
    getMoveTime(Building* target);

};

#endif // PERSON_H
