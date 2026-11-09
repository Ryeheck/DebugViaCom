#include "mainWindow.h"
#include "logView.h"
#include "../core/dataReceiver.h"
#include "loader.h"

#include <QVBoxLayout>
#include <QWidget>
#include <qdialog.h>
#include <qpushbutton.h>
#include <qserialportinfo.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    centralWidget = new QWidget(this);
    mainLayout    = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);
    
    logs = new LogView(this);
    mainLayout->addWidget(logs, 1);

    DataReceiver *receiver = new DataReceiver(this);
    
    QPushButton *btn = new QPushButton("Init", this);
    mainLayout->addWidget(btn);

    connect(btn, &QPushButton::clicked, [this, receiver] () {
        loader diag(this);
        if (diag.exec() == QDialog::Accepted) {
            info selectedInfo = diag.selectedInfo();
            
            receiver->init(selectedInfo);
        }
    });

    QPushButton *startBtn = new QPushButton("Start", this);
    connect(startBtn, &QPushButton::clicked, receiver, &DataReceiver::start);
    mainLayout->addWidget(startBtn);
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destroy";
}

