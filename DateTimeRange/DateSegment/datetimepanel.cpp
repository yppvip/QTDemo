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

    calendar = new CalendarWidget;
    panelLayout = new QVBoxLayout(this);

    panelLayout->addWidget(calendar);
    panelLayout->addLayout(timeLayoutHBox);
}

void DateTimePanel::initTime(int h, int m, int s)
{
    mTime.setHMS(h,m,s);
    mDateTime.setDate(mDate);
    mDateTime.setTime(mTime);
}

void DateTimePanel::initLabelText(QString str)
{
    timeLabel->setText(str);
}

QDateTime DateTimePanel::getDateTime()
{
    mDateTime.setTime(timeEdit->time());
    return mDateTime;
}

void DateTimePanel::slotUpdateDate(QDate currentDate)
{
    mDateTime.setDate(currentDate);
}
