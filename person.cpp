#include "person.h"

Person::Person() : health(0),satiety(0),cash(0),end(0)
{
}

double Person::getMoveTime(Building* target) {
    static const double speed = 10;
    double xMov = target->x() - currentBuilding->x();
    double yMov = target->y() - currentBuilding->y();
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

void Person::processEvent() {

    //Complete current event
    if (personEvent == Move || personEvent == Work) {
        health -= duration;
        satiety -= duration;
    } else if (personEvent == Rest){
        health += 2 * duration; //sleep about 8/24ths of a day. Factor may improve with better houses
        satiety -= duration/2;
    } else if (personEvent == Shop) {
        satiety += duration*24; //Currently eating/feeding
        health -= duration;
    }
    if (health > 24)
        health = 24;
    if (satiety > 16)
        satiety = 16;

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

    //Critical Levels
    if (satiety < minSatiety) {
        if (currentBuilding->buildingType() == Building::Store) {
            duration = (minSatiety - satiety + 2)/24;
            personEvent = Shop;
            end += duration;
        } else {
            duration = getMoveTime(localStore);
            currentBuilding = localStore;
            personEvent = Move;
            end += duration;
        }
        return;
    } else if (health < minHealth) {

        if (currentBuilding->buildingType() == Building::Home) {
            duration = (minHealth - health + 2)/2;
            personEvent = Rest;
            end += duration;
        } else {
            duration = getMoveTime(home);
            currentBuilding = home;
            personEvent = Move;
            end += duration;
        }
        return;
    }

    //calculate time until work starts.
    double tod = fmod(currentTime,24.0);
    if (tod > 16.0)
        tod-=24.0;
    double timeToWork = 8 - tod;

    if (timeToWork < 0) { //the workday has already started
        if (currentBuilding->buildingType() == Building::WorkPlace) {
            duration = (minHealth - health + 2)/2;
            personEvent = Work;
            end += duration;
        } else {
            duration = getMoveTime(workPlace);
            if (timeToWork*-1 + duration < 8.0) {
                currentBuilding = workPlace;
                personEvent = Move;
                end += duration;
                return;
            } else { //we won't make it before the day is over anyway, do smth else

            }
        }
    }
    //else rest or get smth to eat.. what ever we lack the most / slightly depending on where we are :O)


}
