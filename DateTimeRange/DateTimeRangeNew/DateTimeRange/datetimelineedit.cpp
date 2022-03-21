#include "datetimelineedit.h"

DateTimeLineEdit::DateTimeLineEdit(QWidget *parent): QLineEdit(parent),
    startDateTime(QDateTime::currentDateTime()),
    endDateTime(QDateTime::currentDateTime())
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    startDateTime.setTime(QTime(0, 0, 0));
    endDateTime.setTime(QTime(18, 0, 0));
    QString timeStr;
    timeStr = startDateTime.toString("yyyy-MM-dd hh:mm:ss") + "-"
             + endDateTime.toString("yyyy-MM-dd hh:mm:ss");
    setText(timeStr);
    action = new QWidgetAction(this);
    openCalenderBtn = new QToolButton();
    openCalenderBtn->setCursor(Qt::ArrowCursor);
    action->setDefaultWidget(openCalenderBtn);
    this->addAction(action, QLineEdit::TrailingPosition);
    this->setContentsMargins(0, 0, 0, 0);
    this->setStyleSheet("QLineEdit {border: 1px solid #EEE;}"
                      "QLineEdit:focus {border-color: #bbbec4;padding-right:0px}");
    openCalenderBtn->setStyleSheet("QToolButton {width:  16px;"
                     "height: 16px;qproperty-flat: true;"
                     "margin-right: 0px;border: none;border-width: 0;"
                     "border-image: url(calend2.svg) 0 0 0 0;}");
    connect(openCalenderBtn,&QToolButton::clicked,
            this,&DateTimeLineEdit::signalOpenCalender);

}

DateTimeLineEdit::~DateTimeLineEdit()
{

}

void DateTimeLineEdit::slotDateTimeRangeChanged(QDateTime start, QDateTime end)
{
    QString timeStr;
    timeStr = start.toString("yyyy-MM-dd hh:mm:ss") + "-"
             + end.toString("yyyy-MM-dd hh:mm:ss");
    setText(timeStr);
    startDateTime = start;
    endDateTime =end;
}
