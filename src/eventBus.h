#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <qobject.h>
#include <qtmetamacros.h>
#include <qtypes.h>

class EventBus : public QObject
{
    Q_OBJECT

private:
    EventBus() = default;

public:
    static EventBus& instance()
    {
        static EventBus bus;
        return bus;
    }

    EventBus(const EventBus &) = delete;
    EventBus operator=(const EventBus &) = delete;

signals:

};

#endif // EVENTBUS_H