#ifndef LOADER_H
#define LOADER_H

#include <qboxlayout.h>
#include <qcombobox.h>
#include <qobject.h>
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

private:
    void refreshData();
    void connectToPort();

    QVBoxLayout *mainLayout;
    QComboBox *comboPorts;

};

#endif // LOADER_H