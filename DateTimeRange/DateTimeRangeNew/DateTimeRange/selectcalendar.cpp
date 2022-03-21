#include <QFile>
#include <QTextStream>
#include "selectcalendar.h"

SelectCalendar::SelectCalendar(QWidget *parent) :
    QWidget(parent),
    startDateTime(QDateTime::currentDateTime()),
    endDateTime(QDateTime::currentDateTime())
{

    setWindowFlags (Qt::FramelessWindowHint);  //设置窗口无边框
    startDateTime.setTime(QTime(0,0,0));
    endDateTime.setTime(QTime(18,0,0));
    mainLayoutVBox = new QVBoxLayout(this);

    dayInfoLayoutHBox = new QHBoxLayout();
    dayInfoLabel = new QLabel;
    dayInfoLabel->setAlignment(Qt::AlignLeft |
                               Qt::AlignVCenter);
    QString str;
    str = "今天:" + QDateTime::currentDateTime().
                   toString("yyyy-MM-dd");
    dayInfoLabel->setText(str);
    dayInfoSpacerH = new QSpacerItem(0, 0,
                                     QSizePolicy::Expanding,
                                     QSizePolicy::Minimum);
    sureBtn = new QPushButton("确定");
    cancelBtn = new QPushButton("取消");

    dayInfoLayoutHBox->addWidget(dayInfoLabel);
    dayInfoLayoutHBox->addItem(dayInfoSpacerH);
    dayInfoLayoutHBox->addWidget(cancelBtn);
    dayInfoLayoutHBox->addWidget(sureBtn);

    calendarLayoutHBox = new QHBoxLayout;  //管理开始时间和结束时间选择的日历

    startDateLayoutVBox = new QVBoxLayout;
    startCalendar = new QCalendarWidget();
    startTimeEdit = new QTimeEdit;
    startTimeEdit->setDisplayFormat("HH:mm:ss");
    startTimeHBox = new QHBoxLayout;
    startTimeInfoLabel = new QLabel("开始时间:");
    startTimeHBox->addWidget(startTimeInfoLabel);
    startTimeHBox->addStretch();
    startTimeHBox->addWidget(startTimeEdit);
    startTimeHBox->setContentsMargins(0, 0, 5, 0);
    startDateLayoutVBox->addWidget(startCalendar);
    startDateLayoutVBox->addLayout(startTimeHBox);

    endDateLayoutVBox = new QVBoxLayout;
    endCalendar = new QCalendarWidget();
    endTimeEdit = new QTimeEdit();
    endTimeEdit->setDisplayFormat("HH:mm:ss");
    endTimeHBox = new QHBoxLayout;
    endTimeInfoLabel = new QLabel("结束时间:");
    endTimeHBox->addWidget(endTimeInfoLabel);
    endTimeHBox->addStretch();
    endTimeHBox->addWidget(endTimeEdit);
    endTimeHBox->setContentsMargins(0, 0, 5, 0);
    endDateLayoutVBox->addWidget(endCalendar);
    endDateLayoutVBox->addLayout(endTimeHBox);

    calendarLayoutHBox->addLayout(startDateLayoutVBox);
    calendarLayoutHBox->addLayout(endDateLayoutVBox);

    mainLayoutVBox->addLayout(calendarLayoutHBox);
    mainLayoutVBox->addLayout(dayInfoLayoutHBox);

    mainLayoutVBox->setContentsMargins(0, 0, 0, 0);
    mainLayoutVBox->setSpacing(0);

    setWidgetStytle();

    hide();
    setMinimumSize(420,240);
    setMaximumSize(420,240);
    initSignalsAndSlots();
}

SelectCalendar::~SelectCalendar()
{

}

QDateTime SelectCalendar::getStartDateTime()
{
    return startDateTime;
}

QDateTime SelectCalendar::getEndDateTime()
{
    return endDateTime;
}

void SelectCalendar::slotUpdate()
{
    if(isHidden()){
        QString str;
        str = "今天:" + QDateTime::currentDateTime().
                toString("yyyy-MM-dd");

        startCalendar->setSelectedDate(startDateTime.date());
        endCalendar->setSelectedDate(endDateTime.date());

        startTimeEdit->setTime(startDateTime.time());
        endTimeEdit->setTime(endDateTime.time());
        show();
    }
}

void SelectCalendar::slotSureBtnClicked()
{
    QDateTime sDateTime = startDateTime;
    startDateTime.setDate(startCalendar->selectedDate());
    startDateTime.setTime(startTimeEdit->time());

    QDateTime eDateTime = endDateTime;
    endDateTime.setDate(endCalendar->selectedDate());
    endDateTime.setTime(endTimeEdit->time());

    if(startDateTime.secsTo(endDateTime) < 0){  //开始时间在结束时间之后
        startDateTime = sDateTime;
        endDateTime = eDateTime;
        return;   //不做任何处理,继续选择
    }
    else{  //开始时间在结束时间之前
        emit signalUpdateTimeRange(startDateTime,
                                   endDateTime);
        hide();
    }
}

void SelectCalendar::slotCancelBtnClicked()
{
    hide();
}

void SelectCalendar::initSignalsAndSlots()
{
    connect(sureBtn,&QPushButton::clicked,
            this,&SelectCalendar::slotSureBtnClicked);

    connect(cancelBtn,&QPushButton::clicked,
            this,&SelectCalendar::slotCancelBtnClicked);
}

void SelectCalendar::setWidgetStytle()
{
    startCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    endCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    //日期栏现实一二三四五六日，需要下面两条语句
    startCalendar->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
    startCalendar->setLocale(QLocale::Chinese);

    endCalendar->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
    endCalendar->setLocale(QLocale::Chinese);

    //应用样式 apply the qss style
    QFile file("Calendar.qss");  //stylw.qss是自己定义的QSS文件
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();  //读取文件内容
    file.close();


    startCalendar->setStyleSheet(stylesheet);
    endCalendar->setStyleSheet(stylesheet);
// "#qt_calendar_calendarview {background: rgba(15, 15, 15, 255);letter-spacing : 2px;font-size : 12px;color:rgba(240,240,240,255);}"  //修改日期栏的颜色
// "QTableView {alternate-background-color: rgb(15, 15, 15)}"   //修改星期提示的颜色
// "#qt_calendar_navigationbar{background: rgba(15, 15, 15, 255);letter-spacing : 2px;font-size : 12px;}"//修改年月提示栏的颜色
// " QCalendarWidget QAbstractItemView:enabled {color: black; selection-color: white; selection-background-color: rgb(255, 174, 0);font: 15px;}"
//""
//                );


}
