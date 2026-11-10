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

    emit EventBus::instance().logging(typeLog::success, 
                                      "Receiver", "Initialize");
    m_init.store(true);
    return true;
}

bool DataReceiver::init(QSerialPortInfo &info)
{
    if (info.isNull()) {
        emit EventBus::instance().logging(typeLog::error, 
                                          "Receiver", "Info is NULL");
        return false;
    }
    
    serial = new QSerialPort(this);
    serial->setPort(info);

    emit EventBus::instance().logging(typeLog::success, 
                                      "Receiver", "Initialize");
    m_init.store(true);
    return true;
}

void DataReceiver::start()
{
    emit EventBus::instance().logging(typeLog::simple,
                                      "Receiver", "Start...");

    if (!m_init) {
        emit EventBus::instance().logging(typeLog::error, 
                                          "Receiver", "Serial is not init");
        return;
    }
    if (!serial->open(QIODevice::ReadOnly)) {
        emit EventBus::instance().logging(typeLog::error, 
                                          "Receiver", QString("Serial Couldn't open: %1").arg(serial->errorString()));
        return;
    }
    emit EventBus::instance().appendText(QString("Accept text from %1: ").arg(serial->portName()));

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

