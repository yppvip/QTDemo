#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "pushcombox.h"
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    PushCombox* pushComBox;
};
#endif // WIDGET_H
