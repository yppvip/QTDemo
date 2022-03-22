#ifndef DATESEGMENT_H
#define DATESEGMENT_H


//进行时间范围选择，由两个datetime选择widget构成

#include <QWidget>
#include "datetimepanel.h"
class DateSegment : public QWidget
{
    Q_OBJECT
public:
    explicit DateSegment(QWidget *parent = nullptr);
    ~DateSegment();


public slots:
    void slotCancelBtnClicked();
    void slotSureBtnClicked();

    void slotUpdate();  //当打开该控件时更新时间信息
private:
    DateTimePanel* startPanel;
    DateTimePanel* endPanel;
    QHBoxLayout* panelLayoutHBox;

    QLabel* dayLabel;
    QPushButton* cancelBtn;
    QPushButton* sureBtn;
    QHBoxLayout* dayLayoutHBox;

    QVBoxLayout* segmentLayoutVBox;

    QDateTime startDateTime;
    QDateTime endDateTime;
signals:
    void signalUpdate(QDateTime startTime,QDateTime endTime);
};

#endif // DATESEGMENT_H





