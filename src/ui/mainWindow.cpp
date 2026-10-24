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

    QPushButton *btn = new QPushButton(this);
    btn->show();
    mainLayout->addWidget(btn);

    connect(btn, &QPushButton::clicked, [this] () {
        logs->colorLog("DarkSeaGreen", "SUCCESS: ", 
                       "cyan", "Ready read");
        
        logs->text("This is text");

    });

    QPushButton *btn1 = new QPushButton("Clear", this);
    btn1->show();
    mainLayout->addWidget(btn1);

    connect(btn1, &QPushButton::clicked, [this] () {
        logs->clearText();

    });
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destroy";
}

