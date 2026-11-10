#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <qboxlayout.h>
#include <qobject.h>
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
    void appendText(const QString &message);
    void log( const QString &message);
    void colorLog(const QString &firstColor,  const QString &firstMessage,
                  const QString &secondColor = "", const QString &secondMessage = "");
    void acceptText(const QString &message);
    void clearText();  

private:
    QVBoxLayout *vLayout;
    QPlainTextEdit *logText; 
};

#endif // LOGVIEW_H