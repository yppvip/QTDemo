#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "switchbtn.h"
#include <QHBoxLayout>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QWidget* centerWidget;
    QHBoxLayout* hBox;
    SwitchBtn* openBtn;
    SwitchBtn* closeBtn;
};
#endif // MAINWINDOW_H
