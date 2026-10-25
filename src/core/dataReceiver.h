#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <qobject.h>
#include <QSerialPort>
#include <QSerialPortInfo>

class DataReceiver : public QObject
{
    Q_OBJECT

public:
    DataReceiver(QObject *parent = nullptr);
    ~DataReceiver();

public slots:
    bool init();

private:

};

#endif // DATARECEIVER_H