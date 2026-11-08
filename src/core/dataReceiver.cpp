#include "dataReceiver.h"
#include "../eventBus.h"

#include <QSerialPort>
#include <QSerialPortInfo>
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
    serial->setPort(info);

    m_init.store(true);
    return true;
}

DataReceiver::~DataReceiver()
{
    qDebug() << "dataReceiver destroy";
}

