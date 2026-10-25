#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "logView.h"

#include <QMainWindow>
#include <qboxlayout.h>
#include <qwidget.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;

    LogView *logs;
    
};
#endif // MAINWINDOW_H