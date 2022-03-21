#ifndef DATESEGMENT_H
#define DATESEGMENT_H


//进行时间范围选择，由两个datetime选择widget构成

#include <QWidget>

class DateSegment : public QWidget
{
    Q_OBJECT
public:
    explicit DateSegment(QWidget *parent = nullptr);

signals:

};

#endif // DATESEGMENT_H
