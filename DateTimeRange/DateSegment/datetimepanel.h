#ifndef DATETIMEPANEL_H
#define DATETIMEPANEL_H


//由日历和时间编辑组成的操作面板

#include <QWidget>
#include <QDateTime>
#include <QTimeEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "calendarwidget.h"
class DateTimePanel : public QWidget
{
    Q_OBJECT
public:
    explicit DateTimePanel(QWidget *parent = nullptr);
    void initTime(int h,int m,int s);
    void initLabelText(QString str);
    void updateInfo();  //每一次打开时更新时间数据
    QDateTime getDateTime();
public slots:
    void slotUpdateDate(QDate currentDate);
private:
    QLabel* timeLabel;
    QTimeEdit* timeEdit;
    QHBoxLayout* timeLayoutHBox;
    CalendarWidget* calendar;
    QVBoxLayout* panelLayout;



    QDate mDate;
    QTime mTime;
    QDateTime mDateTime;

};

#endif // DATETIMEPANEL_H
