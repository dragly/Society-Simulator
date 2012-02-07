#ifndef PERSON_H
#define PERSON_H

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
    int x;
    int y;

    //Building* currentBuilding;

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

};

#endif // PERSON_H
