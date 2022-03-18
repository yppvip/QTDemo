#ifndef DATETIMERANGE_H
#define DATETIMERANGE_H

#include <QWidget>
#include <QLineEdit>
#include <QDateTime>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCalendarWidget>  //日历控件
#include <QTimeEdit>
#include <QSpacerItem>
#include <QLabel>
#include <QResizeEvent>
#include <QToolButton>
#include <QWidgetAction>
class DateTimeRangeSelect : public QWidget  //用于实现日历弹出与时间选择功能
{
    Q_OBJECT
public:
    explicit DateTimeRangeSelect(QWidget* parent = nullptr);
    ~DateTimeRangeSelect();
    QDateTime getStartDateTime();
    QDateTime getEndDateTime();

public slots:
    void slotUpdate();  //当打开该控件时更新时间信息
    void slotSureBtnClicked();
    void slotCancelBtnClicked();
signals:
    //当选择的时间范围，发生改变时，发生跟新信号
    void signalUpdateTimeRange(QDateTime startDateTime,
                               QDateTime endDateTime);
private:
    void initSignalsAndSlots();

private:
    QVBoxLayout* mainLayoutVBox;  //垂直主布局

    QHBoxLayout* dayInfoLayoutHBox;  //显示今天时间的，方式确定、取消按钮的布局
    QLabel* dayInfoLabel;       //显示今日时间
    QSpacerItem* dayInfoSpacerH;
    QPushButton* sureBtn;
    QPushButton* cancelBtn;

    QHBoxLayout* calendarLayoutHBox;  //管理日历选择的布局

    QVBoxLayout* startDateLayoutVBox; //管理日历和时间控件
    QCalendarWidget* startCalendar;
    QTimeEdit* startTimeEdit;

    QVBoxLayout* endDateLayoutVBox; //管理日历和时间控件
    QCalendarWidget* endCalendar;
    QTimeEdit* endTimeEdit;

    QDateTime startDateTime;
    QDateTime endDateTime;

};


/*****************************************************/

/****************************************************/
class DateTimeRange : public QWidget
{
    Q_OBJECT
public:
    enum OpenLocal{
        up,
        down
    };
    explicit DateTimeRange(QWidget *parent = nullptr);
    ~DateTimeRange();
public slots:
    void slotDateTimeRangeChanged(QDateTime start,
                                  QDateTime end);
signals:
    void signalOpenCalender();

protected:
   virtual void resizeEvent(QResizeEvent *event) override;
private:
    QHBoxLayout* widgetLayout;
    QLineEdit* dateTimeLineEdit;
    QToolButton* openCalenderBtn;
    QWidgetAction* action;
    DateTimeRangeSelect* dateTimeRangeSelect;

    QDateTime startDateTime;
    QDateTime endDateTime;
    OpenLocal calenderOpenLocal = up;  //时间选择框打开的位置

};

#endif // DATETIMERANGE_H
