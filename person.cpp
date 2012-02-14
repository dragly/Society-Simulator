#include "person.h"

PersonStats::PersonStats() : _health(0),_satiety(0),_cash(0),_evStart(0), _duration (0), _evEnd(0), _personEvent(None)
{
}

double Person::getMoveTime(Building* target) {
    static const double speed = 10;
    double xMov = target->x() - pS.currentBuilding()->x();
    double yMov = target->y() - pS.currentBuilding()->y();
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

    pS.finishEvent();

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
    if (pS.satiety() < minSatiety) {
        if (pS.currentBuilding()->buildingType() == Building::Store) {
            pS.duration = (minSatiety - satiety + 2)/24;
            pS.personEvent() = Shop;
            end += duration;
        } else {
            duration = getMoveTime(localStore);
            currentBuilding = localStore;
            personEvent = Move;
            end += duration;
        }
        return;
    } else if (health < minHealth) {

        if (currentBuilding->buildingType() == Building.Home) {
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
        if (currentBuilding->buildingType() == Building.WorkPlace) {
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

void PersonStats::finishEvent () {

    if (personEvent() == None)
        return;

    //Complete current event
    if (personEvent() == Move || personEvent() == Work) {
        _health -= duration;
        _satiety -= duration;
    } else if (personEvent() == Rest){
        _health += 2 * duration; //sleep about 8/24ths of a day. Factor may improve with better houses
        _satiety -= duration/2;
    } else if (personEvent() == Shop) {
        _satiety += duration*24; //Currently eating/feeding
        _health -= duration;
    }
    if (_health > 24)
        _health = 24;
    if (_satiety > 16)
        _satiety = 16;
}
