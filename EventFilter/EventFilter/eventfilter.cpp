#include "eventfilter.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QMatrix>

EventFilter::EventFilter(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent,f)
{
    setWindowTitle("事件过滤");
    label1 = new QLabel;
    image1.load("../EventFilter/image/1.png");
    label1->setAlignment(Qt::AlignHCenter|
                         Qt::AlignVCenter);
    label1->setPixmap(QPixmap::fromImage(image1));

    label2 = new QLabel;
    image2.load("../EventFilter/image/2.png");
    label2->setAlignment(Qt::AlignHCenter|
                         Qt::AlignVCenter);
    label2->setPixmap(QPixmap::fromImage(image2));

    label3 = new QLabel;
    image3.load("../EventFilter/image/3.png");
    label3->setAlignment(Qt::AlignHCenter|
                         Qt::AlignVCenter);
    label3->setPixmap(QPixmap::fromImage(image3));

    stateLabel = new QLabel("鼠标按下标志");
    stateLabel->setAlignment(Qt::AlignHCenter);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(label1);
    layout->addWidget(label2);
    layout->addWidget(label3);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(layout);
    mainLayout->addWidget(stateLabel);

    label1->installEventFilter(this);
    label2->installEventFilter(this);
    label3->installEventFilter(this);
}

EventFilter::~EventFilter()
{
}

bool EventFilter::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == label1)    //首先判断当前事件的对象,左边的label
    {
        //判断发生的事件类型
        if(event->type() == QEvent::MouseButtonPress)
        {
            //将事件event转化为鼠标事件
            QMouseEvent* mouseEvent = (QMouseEvent*)event;
            /* 以下根据鼠标的按键类型分别显示 */
            if(mouseEvent->buttons() & Qt::LeftButton)
            {
                stateLabel->setText("左键按下左边图片");
            }
            else if(mouseEvent->buttons() & Qt::MidButton)
            {
                stateLabel->setText("中键按下左边的图片");
            }
            else if(mouseEvent->buttons() & Qt::RightButton)
            {
                stateLabel->setText("右键按下左边图片");
            }
            /* 显示缩小的图片 */
            QMatrix matrix;
            matrix.scale(1.8, 1.8);
            QImage tempImg = image1.transformed(matrix);
            label1->setPixmap(QPixmap::fromImage(tempImg));
        }

        /* 鼠标释放事件，恢复图片的大小 */
        if(event->type() == QEvent::MouseButtonRelease)
        {
            stateLabel->setText("鼠标释放左边图片");
            label1->setPixmap(QPixmap::fromImage(image1));
        }
    }
    else if(watched == label2)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            // 将事件event转化为鼠标事件
            QMouseEvent* mouseEvent = (QMouseEvent*)event;
            /* 以下根据鼠标的按键类型分别显示 */
            if(mouseEvent->buttons() & Qt::LeftButton)
            {
                stateLabel->setText("左键按下中间图片");
            }
            else if(mouseEvent->buttons() & Qt::MidButton)
            {
                stateLabel->setText("中键按下中间图片");
            }
            else if(mouseEvent->buttons() & Qt::RightButton)
            {
                stateLabel->setText("右键按下中间图片");
            }

            /* 显示缩小的图片 */
            QMatrix matrix;
            matrix.scale(1.8, 1.8);
            QImage temImg = image2.transformed(matrix);
            label2->setPixmap(QPixmap::fromImage(temImg));
        }
        /* 鼠标释放事件的处理,恢复图片的大小 */
        if(event->type() == QEvent::MouseButtonRelease)
        {
            stateLabel->setText("鼠标释放中间图片");
            label2->setPixmap(QPixmap::fromImage(image2));
        }

    }
    else if(watched == label3)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            // 将事件event转化为鼠标事件
            QMouseEvent* mouseEvent = (QMouseEvent*)event;
            /* 以下根据鼠标的按键类型分别显示 */
            if(mouseEvent->buttons() & Qt::LeftButton)
            {
                stateLabel->setText("左键按下右边图片");
            }
            else if(mouseEvent->buttons() & Qt::MidButton)
            {
                stateLabel->setText("中键按下右边图片");
            }
            else if(mouseEvent->buttons() & Qt::RightButton)
            {
                stateLabel->setText("右键按下右边图片");
            }

            /* 显示缩小的图片 */
            QMatrix matrix;
            matrix.scale(1.8, 1.8);
            QImage temImg = image3.transformed(matrix);
            label3->setPixmap(QPixmap::fromImage(temImg));
        }
        /* 鼠标释放事件的处理,恢复图片的大小 */
        if(event->type() == QEvent::MouseButtonRelease)
        {
            stateLabel->setText("鼠标释放中间图片");
            label3->setPixmap(QPixmap::fromImage(image3));
        }

    }

    return QDialog::eventFilter(watched,event);

}




















