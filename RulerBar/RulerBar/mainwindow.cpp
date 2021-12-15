#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centerWidget = new QWidget();
    centerLayout = new QGridLayout();

    rulerBar = new RulerBar();
    slider = new QSlider();
    slider->setOrientation(Qt::Vertical);
    slider->setRange(0,100);
    centerLayout->addWidget(rulerBar,0,0);
    centerLayout->addWidget(slider,0,1);
    centerWidget->setLayout(centerLayout);
    setCentralWidget(centerWidget);

    connect(slider,SIGNAL(valueChanged(int)),
            rulerBar,SLOT(setValue(int)));
    slider->setValue(10);
    slider->valueChanged(10);
}

MainWindow::~MainWindow()
{
    rulerBar->deleteLater();
}

