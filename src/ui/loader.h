#ifndef LOADER_H
#define LOADER_H

#include <qboxlayout.h>
#include <qcombobox.h>
#include <qobject.h>
#include <qserialport.h>
#include <qserialportinfo.h>
#include <qwidget.h>
#include <qwindowdefs.h>
#include <QDialog>
#include <QSerialPort>
#include <QFormLayout>

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
    QComboBox *makeCombo(QWidget *parent, QFormLayout *form, const QString &label,
                     std::initializer_list<std::pair<QString, int>> items = {});

    QVBoxLayout *mainLayout;
    QComboBox *comboPorts;
    QComboBox *comboBaudRate;
    QComboBox *comboFlowControl;
    QComboBox *stopBitsRate;
    QComboBox *comboStopBits;
    QComboBox *comboParity;
    QComboBox *comboDataBits;
};

#endif // LOADER_H