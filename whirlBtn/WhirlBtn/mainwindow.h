#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "whirlbtn.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    WhirlBtn *whirlBtn;
};
#endif // MAINWINDOW_H
