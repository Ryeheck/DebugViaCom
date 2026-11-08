#include "mainWindow.h"
#include "logView.h"
#include "../core/dataReceiver.h"

#include <QVBoxLayout>
#include <QWidget>
#include <qpushbutton.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    centralWidget = new QWidget(this);
    mainLayout    = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);
    
    logs = new LogView(this);
    mainLayout->addWidget(logs, 1);

    DataReceiver *receiver = new DataReceiver(this);
    
    QPushButton *btn = new QPushButton(this);
    mainLayout->addWidget(btn);

}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destroy";
}

