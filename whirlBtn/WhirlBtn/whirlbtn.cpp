#include "whirlbtn.h"

WhirlBtn::WhirlBtn(QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    degree = 90;
}

WhirlBtn::~WhirlBtn()
{

}

void WhirlBtn::setDegree(int deg)
{
    degree = deg;
    update();
}

void WhirlBtn::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    QTransform tranform1;
    int originY = WhirlBtnHeight / 2;
    int originX = WhirlBtnWidth / 2;

    //画红色小三角标志
    const int triangle[3][2] =
    {
        {originX - 2 , 0},
        {originX + 2 , 0},
        {originX , 5}
    };
    painter.setPen(QPen(Qt::red));
    painter.setBrush(QBrush(Qt::red));
    painter.drawPolygon(QPolygon(3, &triangle[0][0]));

    tranform1.translate(originX, originY);
    tranform1.rotate(degree);
    tranform1.translate(-(originX), -(originY));
    painter.setWorldTransform(tranform1);  //旋转下面的内容

    QPen thickPen(palette().foreground(), 1.5); //foreground() 窗口部件的前景色
    QPen midPen(palette().foreground(), 1.0);
    QPen thinPen(palette().foreground(), 0.5);
    QColor niceBlue(150, 150, 200);
    painter.setPen(thinPen);

    //随角度渐变
    QConicalGradient coniGradient(originX, originY, -90.0); //圆锥渐变
    coniGradient.setColorAt(0.0, Qt::darkGray);
    coniGradient.setColorAt(0.2, niceBlue);
    coniGradient.setColorAt(1.0, Qt::white);
    coniGradient.setColorAt(1.0, Qt::darkGray);

    unsigned r = 56;
    painter.setBrush(coniGradient);
    painter.drawEllipse((originX - r), (originY - r), r * 2, r * 2);

    r = 24;
    QRadialGradient haloGradient(originX, originY, r, originX, originY);
    haloGradient.setColorAt(0.0, Qt::lightGray);
    haloGradient.setColorAt(0.8, Qt::darkGray);
    haloGradient.setColorAt(0.9, Qt::white);
    haloGradient.setColorAt(1.0, Qt::black);

    painter.setPen(Qt::NoPen);
    painter.setBrush(haloGradient);

    painter.drawEllipse(originX - r, originY - r, r * 2, 2 * r);

    int rx = 30, ry = 8;
    QLinearGradient knobGradient(originX - rx, originY - ry,
        originX - rx, originY + ry);
    knobGradient.setColorAt(0.0, Qt::black);
    knobGradient.setColorAt(0.2, niceBlue);
    knobGradient.setColorAt(0.3, Qt::lightGray);
    knobGradient.setColorAt(0.8, Qt::black);

    painter.setBrush(knobGradient);
    painter.setPen(thinPen);
    painter.drawRoundedRect(originX - rx, originY - ry, rx * 2,ry*2, 49, 99);

    /*
    for (int i = 0; i < 36; ++i) //绘制刻度
    {
        if (i % 6)
        {
            painter.setPen(midPen);
            painter.drawLine(5, originY, 10, originY);
        }
        else
        {
            painter.setPen(thickPen);
            painter.drawLine(5, originY, 13, originY);

            tranform1.translate(25, originY);
            tranform1.rotate(-90);
            tranform1.translate(-25, -originY);
            painter.setWorldTransform(tranform1);


            painter.drawText(22, originY, QString::number(i / 6));
            tranform1.translate(25, originY);
            tranform1.rotate(90);
            tranform1.translate(-25, -originY);
            painter.setWorldTransform(tranform1);
        }

        tranform1.translate(originX, originY);
        tranform1.rotate(-10);
        tranform1.translate(-originX, -originY);
        painter.setWorldTransform(tranform1);
    }
    */

    painter.setPen(thickPen);
    painter.drawLine(5, originY, 13, originY);
    //写入字符
    tranform1.translate(26, originY);
    tranform1.rotate(-90);
    tranform1.translate(-26, -originY);
    painter.setWorldTransform(tranform1);


    painter.drawText(22, originY, midStr);
    tranform1.translate(26, originY);
    tranform1.rotate(90);
    tranform1.translate(-26, -originY);
    painter.setWorldTransform(tranform1);



    tranform1.translate(originX, originY);
    tranform1.rotate(-60);
    tranform1.translate(-originX, -originY);
    painter.setWorldTransform(tranform1);

    painter.setPen(thickPen);
    painter.drawLine(5, originY, 13, originY);

    tranform1.translate(38, originY);
    tranform1.rotate(-90);
    tranform1.translate(-38, -originY);
    painter.setWorldTransform(tranform1);


    painter.drawText(22, originY-8, leftStr);
    tranform1.translate(38, originY);
    tranform1.rotate(90);
    tranform1.translate(-38, -originY);
    painter.setWorldTransform(tranform1);


    tranform1.translate(originX, originY);
    tranform1.rotate(60);
    tranform1.translate(-originX, -originY);
    painter.setWorldTransform(tranform1);


    tranform1.translate(originX, originY);
    tranform1.rotate(60);
    tranform1.translate(-originX, -originY);
    painter.setWorldTransform(tranform1);

    painter.setPen(thickPen);
    painter.drawLine(5, originY, 13, originY);

    tranform1.translate(38, originY);
    tranform1.rotate(-90);
    tranform1.translate(-38, -originY);
    painter.setWorldTransform(tranform1);


    painter.drawText(22, originY - 8, rightStr);
    tranform1.translate(38, originY);
    tranform1.rotate(90);
    tranform1.translate(-38, -originY);
    painter.setWorldTransform(tranform1);


    tranform1.translate(originX, originY);
    tranform1.rotate(-60);
    tranform1.translate(-originX, -originY);
    painter.setWorldTransform(tranform1);




}

QSize WhirlBtn::sizeHint() const
{
    QSize size = QSize(WhirlBtnWidth, WhirlBtnHeight);
    return size;
}

QSize WhirlBtn::minimumSizeHint() const
{
    QSize size = QSize(WhirlBtnWidth, WhirlBtnHeight);
    return size;
}

void WhirlBtn::mousePressEvent(QMouseEvent* event)
{
    //mouseToPosion(event);
    update();
}

int WhirlBtn::getDegree()
{
    return degree;
}

void WhirlBtn::SetLeftStr(QString str)
{
    leftStr = str;
}

void WhirlBtn::SetMidStr(QString str)
{
    midStr = str;
}

void WhirlBtn::SetRightStr(QString str)
{
    rightStr = str;
}

void WhirlBtn::mouseMoveEvent(QMouseEvent* event)
{
    mouseToPosion(event);
    update();
}

void WhirlBtn::mouseReleaseEvent(QMouseEvent* event)
{
    //mouseToPosion(event);
    updateDegree();
}

void WhirlBtn::mouseToPosion(QMouseEvent* event)
{
    QPoint currentPoint = event->pos();
    double pi = 3.1415927;
    double x = currentPoint.x() - WhirlBtnWidth / 2;
    double y = currentPoint.y() - WhirlBtnHeight / 2;
    //if ((x == 0) && (y <= 0))
    //	degree = 90;
    //else if ((x == 0) && (y < 0))
    //	degree = 270;
    //else if (x > 0)
    //	degree = atan(y / x) * 180 / pi + 180;
    //else if (y > 0)
    //	degree = atan(y / x) * 180 / pi + 360;
    //else
    //	degree = atan(y / x) * 180 / pi;
    //注意: 角度以水平线顺时针为正方向


    if(x>0)
        degree = atan(y / x) * 180 / pi + 180;
    else if(y>0)
        degree = atan(y / x) * 180 / pi;
    else
        degree = atan(y / x) * 180 / pi;

    if (degree < 60)
    {
        degree = 30;
    }
    else if(degree > 120)
    {
        degree = 150;
    }
    else
    {
        degree = 90;
    }

}
