#ifndef DATESEGMENTLINE_H
#define DATESEGMENTLINE_H

#include <QLineEdit>
#include <QLineEdit>
#include <QWidget>
#include <QLineEdit>
#include <QDateTime>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimeEdit>
#include <QSpacerItem>
#include <QLabel>
#include <QToolButton>
#include <QWidgetAction>
class DateSegmentLine : public QLineEdit
{
    Q_OBJECT
public:
    DateSegmentLine(QWidget *parent = nullptr);
public slots:
    void slotDateTimeRangeChanged(QDateTime start,
                                  QDateTime end);

signals:
    void signalOpenCalender();

private:
    QHBoxLayout* widgetLayout;
    QToolButton* openCalenderBtn;
    QWidgetAction* action;

    QDateTime startDateTime;
    QDateTime endDateTime;
};

#endif // DATESEGMENTLINE_H
