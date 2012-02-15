#ifndef SIMULATOREVENT_H
#define SIMULATOREVENT_H

class Entity;

class SimulatorEvent
{
public:
    SimulatorEvent(Entity* target, int time);
    Entity *target() {
        return m_target;
    }
    int time() {
        return m_time;
    }
    void start();

private:
    Entity* m_target;
    int m_time;
};

#endif // SIMULATOREVENT_H
