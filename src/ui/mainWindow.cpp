#include "mainWindow.h"

#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    centralWidget = new QWidget(this);
    mainLayout    = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    

}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destroy";
}

