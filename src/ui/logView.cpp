#include "logView.h"
#include "../eventBus.h"

#include <QVBoxLayout>
#include <QWidget>
#include <qboxlayout.h>
#include <qlocale.h>
#include <qobject.h>
#include <qplaintextedit.h>
#include <qwidget.h>
#include <QPlainTextEdit>
#include <QDateTime>

LogView::LogView(QWidget *parent) 
    : QWidget(parent)
{
    vLayout = new QVBoxLayout(this);
    vLayout->setContentsMargins(0, 0, 0, 0);

    editText = new QPlainTextEdit(this);
    editText->setReadOnly(true);
    editText->document()->setMaximumBlockCount(500);
    vLayout->addWidget(editText);

    logText = new QPlainTextEdit(this);
    logText->setReadOnly(true);
    logText->document()->setMaximumBlockCount(500);
    vLayout->addWidget(logText);

    connect(&EventBus::instance(), &EventBus::logging,      this, &LogView::log);
    connect(&EventBus::instance(), &EventBus::colorLogging, this, &LogView::colorLog);
    connect(&EventBus::instance(), &EventBus::appendText,   this, &LogView::appendText);
    connect(&EventBus::instance(), &EventBus::acceptText,   this, &LogView::acceptText);
}

void LogView::log(typeLog type, const QString &from, const QString &text)
{
    QString time = "[" + QDateTime::currentDateTime().toString("hh:mm:ss") + "]";
    QString color = type ? (type == 2 ? "DarkSeaGreen" : "silver") : "IndianRed";
    QString message = QString("<span style='color:silver;'>[%1]: </span>").arg(from)
                    + QString("<span style='color:%1;'>%2 </span>").arg(color, text);
    
    logText->appendHtml(time + " " + message);
}

void LogView::colorLog(const QString &firstColor,  const QString &firstMessage,
                       const QString &secondColor, const QString &secondMessage)
{
    QString time = "[" + QDateTime::currentDateTime().toString("hh:mm:ss") + "]";
    QString message = QString("<span style='color:%1;'>%2</span>").arg(firstColor, firstMessage)
                    + QString("<span style='color:%1;'>%2</span>").arg(secondColor, secondMessage);

    logText->appendHtml(time + " " + message);
}

void LogView::clearText()
{
    logText->clear();
    editText->clear();
}

void LogView::appendText(const QString &message)
{
    QString text = QString("<span style='color:silver;'>%1</span>").arg(message);
    editText->appendHtml(text);
}

void LogView::acceptText(const QString &message)
{
    editText->moveCursor(QTextCursor::End);
    editText->insertPlainText(message);
}

LogView::~LogView()
{
    qDebug() << "logView destroy";
}

