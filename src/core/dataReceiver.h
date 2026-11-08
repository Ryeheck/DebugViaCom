#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <atomic>
#include <qobject.h>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <qserialport.h>

class DataReceiver : public QObject
{
    Q_OBJECT

public:
    DataReceiver(QObject *parent = nullptr);
    ~DataReceiver();

public slots:
    bool init(QString portName, QSerialPort::BaudRate baudRate, 
              QSerialPort::DataBits dataBits, QSerialPort::StopBits stopBits);
    bool init(QSerialPortInfo &info);
    void start();
private:
    QSerialPort *serial;

    std::atomic<bool> m_init{false};
};

#endif // DATARECEIVER_H