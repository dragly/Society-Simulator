#include "manager.h"
#include "person.h"
#include "entity.h"
#include "simulatorevent.h"

Manager::Manager()
{
}

void Manager::processEvents()
{
}

void Manager::setupTestData()
{
    Person *person = new Person();
    entities.push_front(person);
    SimulatorEvent* event = new SimulatorEvent();

}
