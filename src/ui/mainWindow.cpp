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

    logs = new LogView(this);
    mainLayout->addWidget(logs);
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destroy";
}

