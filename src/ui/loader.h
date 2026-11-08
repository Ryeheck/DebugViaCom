#ifndef LOADER_H
#define LOADER_H

#include <qboxlayout.h>
#include <qcombobox.h>
#include <qobject.h>
#include <qserialportinfo.h>
#include <qwidget.h>
#include <qwindowdefs.h>
#include <QDialog>

class loader : public QDialog
{
    Q_OBJECT

public:
    loader(QWidget *parent = nullptr);
    ~loader();

public slots:
    QSerialPortInfo selectedInfo();
private:
    void refreshData();

    QVBoxLayout *mainLayout;
    QComboBox *comboPorts;
};

#endif // LOADER_H