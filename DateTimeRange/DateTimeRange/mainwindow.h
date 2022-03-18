#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datetimerange.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    DateTimeRange* range;
    QWidget* centerWiget;
    QHBoxLayout* mainLayout;
protected:
    void resizeEvent(QResizeEvent* event);
};
#endif // MAINWINDOW_H
