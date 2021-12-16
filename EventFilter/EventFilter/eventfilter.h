#ifndef EVENTFILTER_H
#define EVENTFILTER_H

#include <QDialog>
#include <QLabel>
#include <QImage>
#include <QEvent>


class EventFilter : public QDialog
{
    Q_OBJECT

public:
    EventFilter(QWidget *parent = nullptr,Qt::WindowFlags f = 0);
    ~EventFilter() ;
public slots:
    bool eventFilter(QObject *, QEvent*);   //QObject的事件监视函数
private:
    QLabel* label1;
    QLabel* label2;
    QLabel* label3;
    QLabel* stateLabel;
    QImage image1;
    QImage image2;
    QImage image3;
};
#endif // EVENTFILTER_H
