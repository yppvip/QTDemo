#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centerWiget = new QWidget;
    setCentralWidget(centerWiget);
    mainLayout = new QHBoxLayout;
    centerWiget->setLayout(mainLayout);
    range = new DateTimeRange();
    mainLayout->addWidget(range);
}

MainWindow::~MainWindow()
{
    range->deleteLater();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    range->resize(range->width(),range->height());
    return QMainWindow::resizeEvent(event);
}

