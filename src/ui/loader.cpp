#include "loader.h"

#include <qboxlayout.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <qwindowdefs.h>
#include <QDialog>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QSerialPortInfo>
#include <QString>

loader::loader(QWidget *parent)
    : QDialog(parent)
{
    mainLayout = new QVBoxLayout(this);
    
    // Ports
    QHBoxLayout *portsHLayout = new QHBoxLayout();
    QLabel *portsLabel = new QLabel("Port: ", this);
    portsHLayout->addWidget(portsLabel);

    comboPorts = new QComboBox(this);
    portsHLayout->addWidget(comboPorts);

    mainLayout->addLayout(portsHLayout);

    /* Buttons */
    // Bottom
    QHBoxLayout *bottomHLayout = new QHBoxLayout();
    QPushButton *refreshBtn = new QPushButton("Refresh", this);
    connect(refreshBtn, &QPushButton::clicked, this, &loader::refreshData);
    bottomHLayout->addWidget(refreshBtn);

    QPushButton *connectBtn = new QPushButton("Connect", this);
    connect(connectBtn, &QPushButton::clicked, this, &loader::connectToPort);
    bottomHLayout->addWidget(connectBtn);

    mainLayout->addLayout(bottomHLayout);

    // Ok & cancel
    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, 
        this);

    connect(buttonBox, &QDialogButtonBox::accepted, this, [this] () {

    });
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    mainLayout->addWidget(buttonBox);
}

void loader::refreshData()
{
    comboPorts->clear();

    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts())
    {
        comboPorts->addItem(info.portName());

        QString desc     = info.description().isEmpty()  ? "None" : info.description();
        QString manufact = info.manufacturer().isEmpty() ? "None" : info.manufacturer();
        
        int idx = comboPorts->count() - 1;
        QString tip = QString("%1\nManufacturer: %2\nVID:PID %3:%4")
        .arg(desc, manufact,
             QString::number(info.vendorIdentifier()), 
             QString::number(info.productIdentifier()));
        comboPorts->setItemData(idx, tip, Qt::ToolTipRole);
    }
}

void loader::connectToPort()
{

}

loader::~loader()
{
    qDebug() << "loader destroy";
}