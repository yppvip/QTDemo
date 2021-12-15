#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "rulerbar.h"
#include <QGridLayout>
#include <QSlider>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QWidget* centerWidget;
    QGridLayout* centerLayout;

    RulerBar* rulerBar;
    QSlider*  slider;

};
#endif // MAINWINDOW_H
