#ifndef EVENTBUS_H
#define EVENTBUS_H

#include <qobject.h>
#include <qserialportinfo.h>
#include <QSerialPort>
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
    void logging(const QString &message);
    void colorLogging(const QString &firstColor,       const QString &firstMessage,
                      const QString &secondColor = "", const QString &secondMessage = "");
    void appendText(const QString &message);
    void connectToPort(QSerialPortInfo &info);
    void connectToPort(QString portName, QSerialPort::BaudRate baudRate, 
                       QSerialPort::DataBits dataBits, QSerialPort::StopBits stopBits);
};

#endif // EVENTBUS_H