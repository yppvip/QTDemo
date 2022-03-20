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
    startDateLayoutVBox->addWidget(startCalendar);
    startDateLayoutVBox->addWidget(startTimeEdit);

    endDateLayoutVBox = new QVBoxLayout;
    endCalendar = new QCalendarWidget();
    endTimeEdit = new QTimeEdit();
    endDateLayoutVBox->addWidget(endCalendar);
    endDateLayoutVBox->addWidget(endTimeEdit);

    calendarLayoutHBox->addLayout(startDateLayoutVBox);
    calendarLayoutHBox->addLayout(endDateLayoutVBox);

    mainLayoutVBox->addLayout(calendarLayoutHBox);
    mainLayoutVBox->addLayout(dayInfoLayoutHBox);

    mainLayoutVBox->setContentsMargins(0, 0, 0, 0);
    mainLayoutVBox->setSpacing(0);

    hide();
    setMinimumSize(240,180);
    setMaximumSize(800,260);
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
    QString str;
    str = "今天:" + QDateTime::currentDateTime().
                   toString("yyyy-MM-dd");

    startCalendar->setSelectedDate(startDateTime.date());
    endCalendar->setSelectedDate(endDateTime.date());

    startTimeEdit->setTime(startDateTime.time());
    endTimeEdit->setTime(endDateTime.time());
    show();
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
