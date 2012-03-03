#include "person.h"

Person::Person() :
    Entity(),
    health(0),
    satiety(0),
    cash(0)
{

}

PersonEvent::PersonEvent()  :
    personEventType(None)
{

}

double Person::getMoveTime(Building* target) {
    static const double speed = 10;
    double xMov = target->x() - currentAction.getCurrentBuilding()->x();
    double yMov = target->y() - currentAction.getCurrentBuilding()->y();
    double distance = sqrt(xMov*xMov + yMov*yMov);
    return distance/speed;
}

double Person::getMoveTime(Building* from, Building* to) {
    static const double speed = 10;
    double xMov = to->x() - from->x();
    double yMov = to->y() - from->y();
    double distance = sqrt(xMov*xMov + yMov*yMov);
    return distance/speed;
}

void Person::processCurrentEvent() {

    finishCurrentAction();

    //if (health < 0 || satiety < 0)
    //   die();

    double workToStore = getMoveTime(workPlace,localStore);
    double workToHome = getMoveTime(workPlace,home);
    double homeToStore = getMoveTime(localStore,home);
    double longestTravel = (workToStore>workToHome) ? workToStore : workToHome;
    //if (homeToStore > longestTravel) longestTravel = homeToStore;

    double minHealth = longestTravel + 8/*worktime*/ + workToStore + 1/*feedtime*/ + homeToStore;
    double minSatiety = longestTravel + 8/*worktime*/ + workToStore;
    //if (minSatiety < workToHome+6+homeToStore) //impossible event
    //    minSatiety = workToHome+6+homeToStore;

    double currentTime = 0; //TODO: pass when calling or make a global
    double end = currentTime;

    //Critical Levels
    if (getSatiety() < minSatiety) {
        if (currentAction.getCurrentBuilding()->buildingType() == Building::Store) {
            currentAction.duration = (2.0f + minSatiety - getSatiety())/24.0;
            currentAction.personEventType = PersonEvent::Shop;
            end += currentAction.getDuration();
        } else {
            currentAction.duration = getMoveTime(localStore);
            currentAction.currentBuilding = localStore;
            currentAction.personEventType = PersonEvent::Move;
            end += currentAction.getDuration();
        }
        return;
    } else if (health < minHealth) {

        if (currentAction.currentBuilding->buildingType() == Building::Home) {
            currentAction.duration = (minHealth - getHealth() + 2)/2;
            currentAction.personEventType = PersonEvent::Rest;
            end += currentAction.duration;
        } else {
            currentAction.duration = getMoveTime(home);
            currentAction.currentBuilding = home;
            currentAction.personEventType = PersonEvent::Move;
            end += currentAction.duration;
        }
        return;
    }

    //calculate time until work starts.
    double tod = fmod(currentTime,24.0);
    if (tod > 16.0)
        tod-=24.0;
    double timeToWork = 8 - tod;

    if (timeToWork < 0) { //the workday has already started
        if (currentAction.currentBuilding->buildingType() == Building::WorkPlace) {
            currentAction.duration = (minHealth - getHealth() + 2)/2;
            currentAction.personEventType = PersonEvent::Work;
            end += currentAction.duration;
        } else {
            currentAction.duration = getMoveTime(workPlace);
            if (timeToWork*-1 + currentAction.duration < 8.0) {
                currentAction.currentBuilding = workPlace;
                currentAction.personEventType = PersonEvent::Move;
                end += currentAction.duration;
                return;
            } else { //we won't make it before the day is over anyway, do smth else

            }
        }
    }
    //else rest or get smth to eat.. what ever we lack the most / slightly depending on where we are :O)


}

void Person::finishCurrentAction() {

    if (currentAction.getPersonEventType() == PersonEvent::None)
        return;

    float duration = currentAction.getDuration();

    //Complete current event
    if (currentAction.getPersonEventType() == PersonEvent::Move || currentAction.getPersonEventType() == PersonEvent::Work) {
        health -= duration;
        satiety -= duration;
    } else if (currentAction.getPersonEventType() == PersonEvent::Rest){
        health += 2 * duration; //sleep about 8/24ths of a day. Factor may improve with better houses
        satiety -= duration/2;
    } else if (currentAction.getPersonEventType() == PersonEvent::Shop) {
        satiety += duration*24; //Currently eating/feeding
        health -= duration;
    }
    if (health > 24)
        health = 24;
    if (satiety > 16)
        satiety = 16;
}
