#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "genericdashboard.h"
#include <QSlider>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QWidget* centerWidget;
    QVBoxLayout* vBox;
    QSlider* slider;
    GenericDashBoard* board;
};
#endif // MAINWINDOW_H
