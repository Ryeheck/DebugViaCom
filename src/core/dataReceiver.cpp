#include "dataReceiver.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <qobject.h>
#include <QDebug>
#include <qserialport.h>

DataReceiver::DataReceiver(QObject *parent) 
    : QObject(parent)
{

}

bool DataReceiver::init()
{
    QSerialPort serial;

    return true;
}

DataReceiver::~DataReceiver()
{
    qDebug() << "dataReceiver destroy";
}

