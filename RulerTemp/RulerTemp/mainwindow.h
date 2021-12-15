#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QSlider>
#include "rulertemp.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QWidget* centerWidget;
    QGridLayout* centerLayout;
    RulerTemp* rulerTemp;
    QSlider* slider;

};
#endif // MAINWINDOW_H
