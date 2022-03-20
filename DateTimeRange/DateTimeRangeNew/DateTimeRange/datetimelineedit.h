#ifndef DATETIMELINEEDIT_H
#define DATETIMELINEEDIT_H

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

class DateTimeLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    enum OpenLocal{
        up,
        down
    };
    DateTimeLineEdit();
    ~DateTimeLineEdit();

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

#endif // DATETIMELINEEDIT_H
