#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    pushComBox = new PushCombox(this);

    pushComBox->addIconItem("1分屏.svg");
    pushComBox->addIconItem("4分屏.svg");
    pushComBox->addIconItem("8分屏.svg");
    pushComBox->addIconItem("9分屏.svg");
    pushComBox->addIconItem("16分屏.svg");

    pushComBox->move(0,200);
    resize(600,400);
}

Widget::~Widget()
{
}

