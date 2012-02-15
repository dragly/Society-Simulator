#ifndef ENTITYEVENT_H
#define ENTITYEVENT_H

class EntityEvent
{
public:
    EntityEvent(int type, int time);
    int time() {
        return m_time;
    }
    int type() {
        return m_type;
    }

private:
    int m_type;
    int m_time;
};

#endif // ENTITYEVENT_H
