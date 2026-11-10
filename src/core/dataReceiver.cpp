#include "dataReceiver.h"
#include "../eventBus.h"
#include "../ui/loader.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <qevent.h>
#include <qlogging.h>
#include <qobject.h>
#include <QDebug>
#include <qserialport.h>
#include <qserialportinfo.h>

DataReceiver::DataReceiver(QObject *parent) 
    : QObject(parent)
{

}

bool DataReceiver::init(info setting)
{
    serial = new QSerialPort(this);
    serial->setPortName(setting.portName);
    serial->setBaudRate(setting.baudRate);
    serial->setDataBits(setting.dataBits);
    serial->setParity(setting.parity);
    serial->setStopBits(setting.stopBits);
    serial->setFlowControl(setting.flowControl);

    m_init.store(true);
    qDebug() << "[DATARECEIVER] initialize";
    return true;
}

bool DataReceiver::init(QSerialPortInfo &info)
{
    if (info.isNull()) {
        qDebug() << "info is NULL";
        return false;
    }
    
    serial = new QSerialPort(this);
    serial->setPort(info);

    m_init.store(true);
    qDebug() << "[DATARECEIVER] initialize";
    return true;
}

void DataReceiver::start()
{
    if (!m_init) {
        qDebug() << "Serial not init";
        return;
    }
    if (!serial->open(QIODevice::ReadOnly)) {
        qDebug() << "Serial Couldn't open: " << serial->errorString();
        return;
    }
    emit EventBus::instance().colorLogging("silver", 
                                           QString("Accept text from: %1").arg(serial->portName()));
    
    connect(serial, &QSerialPort::readyRead, [this] () {
        QByteArray data = serial->readAll();
        QString output = QString::fromUtf8(data);

        emit EventBus::instance().acceptText(output);
    });
}

DataReceiver::~DataReceiver()
{
    qDebug() << "dataReceiver destroy";
}

