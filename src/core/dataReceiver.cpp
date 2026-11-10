#include "dataReceiver.h"
#include "../eventBus.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <qevent.h>
#include <qobject.h>
#include <QDebug>
#include <qserialport.h>
#include <qserialportinfo.h>

DataReceiver::DataReceiver(QObject *parent) 
    : QObject(parent)
{

}

bool DataReceiver::init(QString portName, QSerialPort::BaudRate baudRate, 
                        QSerialPort::DataBits dataBits, QSerialPort::StopBits stopBits)
{
    serial = new QSerialPort(this);
    serial->setPortName(portName);
    serial->setBaudRate(baudRate);
    serial->setDataBits(dataBits);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(stopBits);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    m_init.store(true);
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

