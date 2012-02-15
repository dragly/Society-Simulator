#ifndef MANAGER_H
#define MANAGER_H

#include <list>

class SimulatorEvent;
class Entity;

class Manager
{
public:
    Manager();
    void processEvents();
    void setupTestData();
private:
    std::list<SimulatorEvent*> events;
    std::list<Entity*> entities;
};

#endif // MANAGER_H
