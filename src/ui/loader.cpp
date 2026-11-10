#include "loader.h"
#include "../eventBus.h"
#include "logView.h"

#include <qboxlayout.h>
#include <initializer_list>
#include <qcombobox.h>
#include <qdebug.h>
#include <qdialog.h>
#include <qformlayout.h>
#include <qlabel.h>
#include <qlogging.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qserialport.h>
#include <qserialportinfo.h>
#include <qwidget.h>
#include <QDialog>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QSerialPortInfo>
#include <QString>
#include <QFormLayout>
#include <utility>

loader::loader(QWidget *parent)
    : QDialog(parent)
{
    mainLayout = new QVBoxLayout(this);
    QFormLayout *form = new QFormLayout();
    mainLayout->addLayout(form);

    // Ports
    comboPorts = makeCombo(this, form, "Ports:");

    // Baud rate
    comboBaudRate = makeCombo(this, form, "Baud rate:", {
        {"115200", QSerialPort::Baud115200},
        {"57600",  QSerialPort::Baud57600},
        {"38400",  QSerialPort::Baud38400},
        {"19200",  QSerialPort::Baud19200},
        {"9600",   QSerialPort::Baud9600},
        {"4800",   QSerialPort::Baud4800},
        {"2400",   QSerialPort::Baud2400},
        {"1200",   QSerialPort::Baud1200}
    });
    
    // Data bits
    comboDataBits = makeCombo(this, form, "Data bits:", {
        {"8", QSerialPort::Data8},
        {"7", QSerialPort::Data7},
        {"6", QSerialPort::Data6},
        {"5", QSerialPort::Data5}
    });

    // Parity
    comboParity = makeCombo(this, form, "Parity:", {
        {"No",    QSerialPort::NoParity},
        {"Even",  QSerialPort::EvenParity},
        {"Odd",   QSerialPort::OddParity},
        {"Space", QSerialPort::SpaceParity},
        {"Mark",  QSerialPort::MarkParity},
    });

    // Stop bits
    comboStopBits = makeCombo(this, form, "Stop bits:", {
        {"1",       QSerialPort::OneStop},
        {"1 & 0.5", QSerialPort::OneAndHalfStop},
        {"2",       QSerialPort::TwoStop}
    });

    // Flow Control
    comboFlowControl = makeCombo(this, form, "Flow control:", {
        {"No control",       QSerialPort::NoFlowControl},
        {"Hardware control", QSerialPort::HardwareControl},
        {"Software control", QSerialPort::SoftwareControl}
    });

    /* Buttons */
    // Bottom
    QHBoxLayout *bottomHLayout = new QHBoxLayout();
    QPushButton *refreshBtn = new QPushButton("Refresh", this);
    connect(refreshBtn, &QPushButton::clicked, this, &loader::refreshData);
    bottomHLayout->addWidget(refreshBtn);

    QPushButton *connectBtn = new QPushButton("Connect", this);
    // connect(connectBtn, &QPushButton::clicked, this, /* Comming soon... */);
    bottomHLayout->addWidget(connectBtn);

    mainLayout->addLayout(bottomHLayout);

    // Ok & cancel
    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, 
        this);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    mainLayout->addWidget(buttonBox);
}

void loader::refreshData()
{
    emit EventBus::instance().logging(typeLog::simple, 
                                      "Loader", "Refresh");
    
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

QComboBox *loader::makeCombo(QWidget *parent, QFormLayout *form, const QString &label,
                     std::initializer_list<std::pair<QString, int>> items)
{
    QComboBox *combo = new QComboBox(parent);
    for (const auto &[name, value] : items)
        combo->addItem(name, value);
    form->addRow(label, combo);
    
    return combo;
}

info loader::selectedInfo()
{
    info selectedInfo;
    selectedInfo.portName = comboPorts->currentText();
    
    selectedInfo.flowControl = static_cast<QSerialPort::FlowControl>(comboFlowControl->currentData().toInt());
    selectedInfo.baudRate    = static_cast<QSerialPort::BaudRate>(comboBaudRate->currentData().toInt());
    selectedInfo.dataBits    = static_cast<QSerialPort::DataBits>(comboDataBits->currentData().toInt());
    selectedInfo.stopBits    = static_cast<QSerialPort::StopBits>(comboStopBits->currentData().toInt());
    selectedInfo.parity      = static_cast<QSerialPort::Parity>(comboParity->currentData().toInt());
    
    emit EventBus::instance().logging(typeLog::simple, 
                                      "Loader", QString("info: %1").arg(selectedInfo.portName));
    return selectedInfo;
}

loader::~loader()
{
    qDebug() << "[LOADER] destroy";
}