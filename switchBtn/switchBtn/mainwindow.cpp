#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    hBox = new QHBoxLayout();

    openBtn = new SwitchBtn();
    openBtn->setMaximumHeight(30);
    openBtn->setMinimumWidth(60);
    closeBtn = new SwitchBtn();
    closeBtn->setMaximumHeight(30);
    closeBtn->setMinimumWidth(60);
    closeBtn->setChecked(true);

    hBox->addWidget(openBtn);
    hBox->addWidget(closeBtn);


    centerWidget = new QWidget();
    centerWidget->setLayout(hBox);
    setCentralWidget(centerWidget);

}

MainWindow::~MainWindow()
{
}

