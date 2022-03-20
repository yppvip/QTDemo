#ifndef SELECTCALENDAR_H
#define SELECTCALENDAR_H
//该类进行时间范围选择功能


#include <QWidget>
#include <QDateTime>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCalendarWidget>  //日历控件
#include <QTimeEdit>
#include <QSpacerItem>
#include <QLabel>
#include <QPushButton>
class SelectCalendar : public QWidget
{
    Q_OBJECT
public:
    explicit SelectCalendar(QWidget *parent = nullptr);
    ~SelectCalendar();
    QDateTime getStartDateTime();
    QDateTime getEndDateTime();

public slots:
    void slotUpdate();  //当打开该控件时更新时间信息
    void slotSureBtnClicked(); //确认按钮按下时，更新信息
    void slotCancelBtnClicked(); //取消按钮按下

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

#endif // SELECTCALENDAR_H
