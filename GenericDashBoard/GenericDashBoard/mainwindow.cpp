#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    board = new GenericDashBoard();
    slider = new QSlider();
    slider->setOrientation(Qt::Horizontal);
    slider->setRange(0,240);
    connect(slider,SIGNAL(valueChanged(int)),
            board,SLOT(setValue(int)));

    vBox = new QVBoxLayout();
    vBox->addWidget(board);
    vBox->addWidget(slider);

    centerWidget = new QWidget();
    centerWidget->setLayout(vBox);
    setCentralWidget(centerWidget);
    resize(400,400);
}

MainWindow::~MainWindow()
{
    board->deleteLater();
}

