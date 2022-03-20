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
    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete range;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    return QMainWindow::resizeEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    return QMainWindow::mouseMoveEvent(event);
}

