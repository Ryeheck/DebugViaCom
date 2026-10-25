#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include <qobject.h>
#include <qwidget.h>

class DataReceiver : public QObject
{
    Q_OBJECT

public:
    DataReceiver(QObject *parent = nullptr);
    ~DataReceiver();

public slots:

private:

};

#endif // DATARECEIVER_H