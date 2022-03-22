#include "mainwindow.h"
#include <QtDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centerWidget = new QWidget;
    setCentralWidget(centerWidget);
    mainLayout = new QHBoxLayout;
    centerWidget->setLayout(mainLayout);

    dateLineEdit = new DateSegmentLine;
    mainLayout->addWidget(dateLineEdit);

    dateSegment = new DateSegment(centerWidget);

    connect(dateLineEdit,&DateSegmentLine::signalOpenCalender,
           dateSegment,&DateSegment::slotUpdate);
    connect(dateLineEdit,&DateSegmentLine::signalOpenCalender,
            this,&MainWindow::slotOpenBtnClicked);

    connect(dateSegment,&DateSegment::signalUpdate,
            dateLineEdit,&DateSegmentLine::slotDateTimeRangeChanged);


}

MainWindow::~MainWindow()
{

}

void MainWindow::slotOpenBtnClicked()
{
    QPoint lineEditPos = dateLineEdit->pos();
    dateSegment->move(lineEditPos.x(),
                      lineEditPos.y() - dateSegment->height());
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QPoint lineEditPos = dateLineEdit->pos();
    dateSegment->move(lineEditPos.x(),
                      lineEditPos.y() - dateSegment->height());
//    qDebug()<< dateSegment->isHidden() << dateSegment->pos().x() << " "<< dateSegment->pos().y()
//            << " "<< dateSegment->size()
//            << dateLineEdit->pos() << " "<< dateLineEdit->size() ;
    return QMainWindow::resizeEvent(event);
}

