#include "mainWindow.h"
#include "logView.h"

#include <QVBoxLayout>
#include <QWidget>
#include <qpushbutton.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    centralWidget = new QWidget(this);
    mainLayout    = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    LogView *logs = new LogView(this);
    mainLayout->addWidget(logs);

    QPushButton *btn = new QPushButton(this);
    btn->show();
    mainLayout->addWidget(btn);

    connect(btn, &QPushButton::clicked, [this, logs] () {
        logs->log("QpushButton");
        logs->colorLog("red", "Color: ", "blue", "ready&");
        
        logs->colorLog("green", "Warning: ");
    });
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destroy";
}

