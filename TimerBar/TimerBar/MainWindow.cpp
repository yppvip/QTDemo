#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    timeBar = new TimeBar(this);
    QDateTime sTime(QDate(2022,3,17),QTime(8,30,00,00));
    QDateTime eTime(QDate(2022,3,17),QTime(18,30,00,00));
    TimeRange range;
    range.startTime = sTime;
    range.endTime = eTime;
    QVector<TimeRange> tVec;
    tVec <<range;
    timeBar->setTimeRange(tVec);
}

MainWindow::~MainWindow()
{
    timeBar->deleteLater();
}

