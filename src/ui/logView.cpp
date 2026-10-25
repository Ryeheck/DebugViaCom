#include "logView.h"

#include <QVBoxLayout>
#include <QWidget>
#include <qlocale.h>
#include <qobject.h>
#include <qplaintextedit.h>
#include <qwidget.h>
#include <QPlainTextEdit>
#include <QDateTime>

LogView::LogView(QWidget *parent) 
    : QWidget(parent)
{
    logText = new QPlainTextEdit(this);
    logText->setReadOnly(true);
    logText->document()->setMaximumBlockCount(500);
    logText->show();

}

void LogView::log(const QString &message)
{
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString qTime = "[" + time + "]";

    logText->appendHtml( qTime + " " + message);
}

void LogView::colorLog(const QString &firstColor,  const QString &firstMessage,
                       const QString &secondColor, const QString &secondMessage)
{
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString qTime = "[" + time + "]";
    QString message = QString("<span style='color:%1;'>%2</span>").arg(firstColor, firstMessage)
                    + QString("<span style='color:%1;'>%2</span>").arg(secondColor, secondMessage);

    logText->appendHtml(qTime + " " + message);
}

void LogView::clearText()
{
    logText->clear();

}

void LogView::text(const QString &message)
{
    logText->appendHtml(message);
}

LogView::~LogView()
{
    qDebug() << "logView destroy";
}

