#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centerWidget = new QWidget();
    setCentralWidget(centerWidget);
    mainLayout = new QHBoxLayout();
    centerWidget->setLayout(mainLayout);

    dateTimeLineEdit = new DateTimeLineEdit;
    selectCalendar = new SelectCalendar(this);

    QPoint lineEditPos = dateTimeLineEdit->pos();
    selectCalendar->move(lineEditPos.x(),
                         lineEditPos.y() - selectCalendar->height());

    mainLayout->addWidget(dateTimeLineEdit);


    connect(dateTimeLineEdit,&DateTimeLineEdit::signalOpenCalender,
            selectCalendar,&SelectCalendar::slotUpdate);
    connect(dateTimeLineEdit,&DateTimeLineEdit::signalOpenCalender,
            this,&MainWindow::slotUpdateSelectpos );

    connect(selectCalendar,&SelectCalendar::signalUpdateTimeRange,
            dateTimeLineEdit,&DateTimeLineEdit::slotDateTimeRangeChanged);
    resize(800,600);
}

MainWindow::~MainWindow()
{
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QPoint lineEditPos = dateTimeLineEdit->pos();
    selectCalendar->move(lineEditPos.x(),
                         lineEditPos.y() - selectCalendar->height());
    return QMainWindow::resizeEvent(event);
}

void MainWindow::slotUpdateSelectpos()
{
    QPoint lineEditPos = dateTimeLineEdit->pos();
    selectCalendar->move(lineEditPos.x(),
                         lineEditPos.y() - selectCalendar->height());
}
