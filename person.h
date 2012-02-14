#ifndef PERSON_H
#define PERSON_H

#include "building.h"
#include "math.h"

//action
enum PersonEvent {
    None,
    Move,
    Work,
    Rest,
    Shop
    //etc
};

class PersonStats {
public:
    PersonStats();
    void finishEvent();
    void createEvent();

    double health() { return _health; }
    double satiety() { return _satiety; }
    double cash() { return _cash; }

    PersonEvent personEvent() { return _personEvent; }
    double duration() { return _duration; }
    double evEnd() { return _evEnd; }
    double evStart() { return _evStart; }
    Building* currentBuilding() { return _currentBuilding; }
    Building* destination() { return _destination; }


private:
    double _health; //rest
    double _satiety; //hunger/food
    double _cash;

    PersonEvent _personEvent;
    double _duration;
    double _evEnd;
    double _evStart;

    Building* _currentBuilding;
    Building* _destination;
};

class Person
{
public:
    Person();
private:

    PersonStats pS;

    Building* workPlace;
    Building* localStore; //For now, only use one store
    Building* home;

    void processEvent();

    double  getMoveTime(Building* from, Building* to);
    double getMoveTime(Building* target);

};

#endif // PERSON_H
