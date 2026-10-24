#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <qplaintextedit.h>
#include <qwidget.h>
#include <QPlainTextEdit>

class LogView : public QWidget
{
    Q_OBJECT

public:
    LogView(QWidget *parent = nullptr);
    ~LogView();

public slots:
    void log(const QString &message);
    void colorLog(const QString &firstColor,  const QString &firstMessage,
                  const QString &secondColor = "", const QString &secondMessage = "");

private:
    QPlainTextEdit *logText; 
};

#endif // LOGVIEW_H