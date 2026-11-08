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

bool DataReceiver::init()
{
    QSerialPort serial;

    return true;
}


void DataReceiver::existsPorts()
{
    emit EventBus::instance().colorLogging("green", "start to find ports");

    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts())
    {
        /*
        QString portName = info.portName();
        QString desc = info.description();
        QString manufact = info.manufacturer();
        int vendor = info.vendorIdentifier();
        int product = info.productIdentifier();
        */

        emit EventBus::instance().logging(QString("port: %1").arg(info.portName())); 
        emit EventBus::instance().logging(QString("description: %1").arg(info.description()));
        emit EventBus::instance().logging(QString("manufactur: %1").arg(info.manufacturer()));
        emit EventBus::instance().logging(QString("vendor: %1").arg(info.vendorIdentifier()));
        emit EventBus::instance().logging(QString("product: %1").arg(info.productIdentifier()));
    }
}

DataReceiver::~DataReceiver()
{
    qDebug() << "dataReceiver destroy";
}

