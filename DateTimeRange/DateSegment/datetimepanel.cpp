#include "datetimepanel.h"

DateTimePanel::DateTimePanel(QWidget *parent) : QWidget(parent),
    mDate(QDate::currentDate())
{
    timeLabel = new QLabel;
    timeEdit = new QTimeEdit;
    timeEdit->setDisplayFormat("HH:mm:ss");
    timeLayoutHBox = new QHBoxLayout;
    timeLayoutHBox->addWidget(timeLabel);
    timeLayoutHBox->addStretch();
    timeLayoutHBox->addWidget(timeEdit);
    timeLayoutHBox->setContentsMargins(0, 0, 0, 0);
    timeLayoutHBox->setSpacing(0);
    calendar = new CalendarWidget;
    panelLayout = new QVBoxLayout(this);

    panelLayout->addWidget(calendar);
    panelLayout->addLayout(timeLayoutHBox);
    panelLayout->setContentsMargins(0, 5, 0, 0);
    panelLayout->setSpacing(0);
}

void DateTimePanel::initTime(int h, int m, int s)
{
    mTime.setHMS(h,m,s);
    timeEdit->setTime(mTime);
    mDateTime.setDate(mDate);
    mDateTime.setTime(mTime);
}

void DateTimePanel::initLabelText(QString str)
{
    timeLabel->setText(str);
}

void DateTimePanel::updateInfo()
{
    timeEdit->setTime(mTime);
    calendar->setSelectedDate(mDate);
}

QDateTime DateTimePanel::getDateTime()
{
    mDateTime.setTime(timeEdit->time());
    mDateTime.setDate(calendar->getDate());
    mTime = timeEdit->time();
    mDate = calendar->getDate();
    return mDateTime;
}

void DateTimePanel::slotUpdateDate(QDate currentDate)
{
    mDateTime.setDate(currentDate);
    mDate = currentDate;
}
