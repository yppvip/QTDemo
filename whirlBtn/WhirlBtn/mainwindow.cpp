#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    whirlBtn = new WhirlBtn();
    setCentralWidget(whirlBtn);
}

MainWindow::~MainWindow()
{
    whirlBtn->deleteLater();
}

