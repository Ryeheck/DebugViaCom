#include "dataReceiver.h"

#include <QVBoxLayout>
#include <QWidget>
#include <qlocale.h>
#include <qobject.h>
#include <qplaintextedit.h>
#include <qwidget.h>
#include <QPlainTextEdit>
#include <QDateTime>

DataReceiver::DataReceiver(QObject *parent) 
    : QObject(parent)
{

}

DataReceiver::~DataReceiver()
{
    qDebug() << "dataReceiver destroy";
}

