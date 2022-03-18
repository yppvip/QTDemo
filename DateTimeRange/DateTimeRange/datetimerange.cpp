#include "datetimerange.h"

DateTimeRangeSelect::DateTimeRangeSelect(QWidget *parent) :
    QWidget(parent),
    startDateTime(QDateTime::currentDateTime()),
    endDateTime(QDateTime::currentDateTime())
{

    setWindowFlags (Qt::CustomizeWindowHint);
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

    hide();
    setMinimumSize(240,180);
    setMaximumSize(400,240);
    initSignalsAndSlots();
}

DateTimeRangeSelect::~DateTimeRangeSelect()
{

}

QDateTime DateTimeRangeSelect::getStartDateTime()
{
    return startDateTime;
}

QDateTime DateTimeRangeSelect::getEndDateTime()
{
    return endDateTime;
}

void DateTimeRangeSelect::slotUpdate()
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

void DateTimeRangeSelect::slotSureBtnClicked()
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

void DateTimeRangeSelect::slotCancelBtnClicked()
{
    hide();
}

void DateTimeRangeSelect::initSignalsAndSlots()
{
    connect(sureBtn,&QPushButton::clicked,
            this,&DateTimeRangeSelect::slotSureBtnClicked);

    connect(cancelBtn,&QPushButton::clicked,
            this,&DateTimeRangeSelect::slotCancelBtnClicked);
}




DateTimeRange::DateTimeRange(QWidget *parent) : QWidget(parent)
{
    widgetLayout = new QHBoxLayout(this);
    dateTimeLineEdit = new QLineEdit();
    widgetLayout->addWidget(dateTimeLineEdit);

    action = new QWidgetAction(dateTimeLineEdit);
    openCalenderBtn = new QToolButton();
    openCalenderBtn->setCursor(Qt::ArrowCursor);
    action->setDefaultWidget(openCalenderBtn);
    dateTimeLineEdit->addAction(action, QLineEdit::TrailingPosition);
    dateTimeLineEdit->setContentsMargins(0, 0, 0, 0);
    dateTimeLineEdit->setStyleSheet("QLineEdit {border: 1px solid #EEE;}"
                      "QLineEdit:focus {border-color: #bbbec4;padding-right:0px}");
    openCalenderBtn->setStyleSheet("QToolButton {width:  16px;"
                     "height: 16px;qproperty-flat: true;"
                     "margin-right: 0px;border: none;border-width: 0;"
                     "border-image: url(calend2.svg) 0 0 0 0;}");


    dateTimeRangeSelect = new DateTimeRangeSelect();

    connect(openCalenderBtn,&QToolButton::clicked,
            dateTimeRangeSelect,&DateTimeRangeSelect::slotUpdate);

    QString timeStr;
    startDateTime = dateTimeRangeSelect->getStartDateTime();
    endDateTime = dateTimeRangeSelect->getEndDateTime();
    timeStr = startDateTime.toString("yyyy-MM-dd hh:mm:ss") + "-"
             + endDateTime.toString("yyyy-MM-dd hh:mm:ss");
    dateTimeLineEdit->setText(timeStr);

    //将dateTimeRangeSelect设置到LineEdit周围
    if(calenderOpenLocal == up){  //从上面打开
        QPoint lineEditPos = this->mapToGlobal(this->pos());  //获得在屏幕中的坐标
        dateTimeRangeSelect->move(lineEditPos.x(),lineEditPos.y() - dateTimeLineEdit->height()
                                  - dateTimeRangeSelect->height());
    }
    else{
        QPoint lineEditPos = this->mapToGlobal(this->pos());  //获得在屏幕中的坐标
        dateTimeRangeSelect->move(lineEditPos.x(),lineEditPos.y() + dateTimeLineEdit->height() );
    }
    setMaximumSize(200,60);
}

DateTimeRange::~DateTimeRange()
{
//    dateTimeRangeSelect->deleteLater();
    action->deleteLater();
    openCalenderBtn->deleteLater();
}

void DateTimeRange::slotDateTimeRangeChanged(QDateTime start, QDateTime end)
{
    QString timeStr;
    timeStr = start.toString("yyyy-MM-dd hh:mm:ss") + "-"
             + end.toString("yyyy-MM-dd hh:mm:ss");
    dateTimeLineEdit->setText(timeStr);
    startDateTime = start;
    endDateTime =end;
}

void DateTimeRange::resizeEvent(QResizeEvent *event)
{
//    resize(dateTimeLineEdit->width(),
//           dateTimeLineEdit->height());

    if(calenderOpenLocal == up){  //从上面打开
        QPoint lineEditPos = this->mapToGlobal(this->pos());  //获得在屏幕中的坐标
        dateTimeRangeSelect->move(lineEditPos.x(),lineEditPos.y() - dateTimeLineEdit->height()-
                                  dateTimeRangeSelect->height());
    }
    else{
        QPoint lineEditPos = this->mapToGlobal(this->pos());  //获得在屏幕中的坐标
        dateTimeRangeSelect->move(lineEditPos.x(),lineEditPos.y() + dateTimeLineEdit->height() );
    }
    return QWidget::resizeEvent(event);
}
