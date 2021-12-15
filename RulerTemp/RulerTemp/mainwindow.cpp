#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centerLayout = new QGridLayout();
    centerWidget = new QWidget();
    rulerTemp = new RulerTemp();
    slider = new QSlider();
    slider->setRange(-30,140);
    centerLayout->addWidget(rulerTemp,0,0);
    centerLayout->addWidget(slider,0,1);

    connect(slider,SIGNAL(valueChanged(int)),
            rulerTemp,SLOT(setValue(int)));
    slider->valueChanged(0);



    centerWidget->setLayout(centerLayout);
    setCentralWidget(centerWidget);

}

MainWindow::~MainWindow()
{
    rulerTemp->deleteLater();
}

