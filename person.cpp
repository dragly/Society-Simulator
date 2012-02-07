#include "person.h"

Person::Person() : health(0),satiety(0),cash(0),x(0),y(0),end(0)
{
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
        satiety -= duration/2;
    }
    if (health > 24)
        health = 24;
    if (satiety > 16)
        satiety = 16;

    //if (health < 0 || satiety < 0)
    //   die();

    //Decide on and commence new event
         //For moves, set the coordinate/target when the movement starts


    //Make sure work will be reached in time
        //duration = distance/speed;
}
