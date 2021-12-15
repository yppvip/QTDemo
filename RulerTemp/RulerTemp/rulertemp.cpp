#include "rulertemp.h"

RulerTemp::RulerTemp(QWidget *parent) : QWidget(parent)
{
    setRange(-30, 140);
    setPrecision(1);
    setLongStep(10);
    setShortStep(5);
    setSpace(2);
    setAnimation(true);
    setAnimationStep(10);
    setShowUserValue(false);
    setBgColorStart(QColor(255, 255, 255));
    setBgColorEnd(QColor(255, 255, 255));
    setLineColor(QColor(150, 20, 140));
    setBarBgColor(QColor(50, 200, 200));
    setBarColor(QColor(200, 40, 20));
    setBarPosition(BarPosition::BarPosition_Center);
    setTickPosition(TickPosition::TickPosition_Right);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
        this, &RulerTemp::updateTimerout);

    setValue(40);
    currentValue = 40;
}


void RulerTemp::updateTimerout()
{

    if (RulerTemp::value > RulerTemp::currentValue)
    {
        RulerTemp::currentValue += 2;
        if (RulerTemp::value <= RulerTemp::currentValue)
        {
            RulerTemp::currentValue = RulerTemp::value;
            timer->stop();
        }
    }
    else if (RulerTemp::value < RulerTemp::currentValue)
    {
        RulerTemp::currentValue -= 2;
        if (RulerTemp::value >= RulerTemp::currentValue)
        {
            RulerTemp::currentValue = RulerTemp::value;
            timer->stop();
        }
    }

    update();
}

RulerTemp::~RulerTemp()
{
    timer->deleteLater();
}

void RulerTemp::resizeEvent(QResizeEvent*)
{

    if (width() > 70 && height() > 150)
    {
        barWidth = 20;
        barHeight = height() - 60;  //温度计柱的高度
        radius = 30;                //温度计球的半径
        targetX = width() / 2 ;     //温度计中轴线的位置,确定温度计在widget中的绘图位置,此处设置为中心
    /*	barRect = QRectF(width() / 2 - 10, 0, barWidth, barHeight);
        circleRect = QRectF(width() / 2 - radius,barHeight+30, radius, radius);*/
    }
    else if (width() * 3 > height())
    {
        radius = height() / 8;     //温度计球的半径
        barWidth = radius * 2 / 3; //温度计柱的宽度
        barHeight = height() - 2 * radius;  //温度计柱的高度
        targetX = width()/2;       //绘制温度计的位置
        //barRect = QRectF(width() / 2 - barWidth / 2, 0, barWidth, barHeight);
        //circleRect = QRectF(width() / 2 - radius, barHeight+20, radius, radius);
    }
    else
    {
        radius = (width() - 10) / 2;
        barWidth = radius * 2 / 3;
        barHeight = height() - 2 * radius;
        targetX = width() / 2;
        //barRect = QRectF(width() / 2 - barWidth / 2, 0, barWidth, barHeight);
        //circleRect = QRectF(width() / 2 - radius, barHeight+20, radius, radius);
    }
}

void RulerTemp::paintEvent(QPaintEvent*)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);

    //绘制标尺及刻度尺
    if (tickPosition == TickPosition_Left) {
        drawRuler(&painter, 0);
    }
    else if (tickPosition == TickPosition_Right) {
        drawRuler(&painter, 1);
    }
    else if (tickPosition == TickPosition_Both) {
        drawRuler(&painter, 0);
        drawRuler(&painter, 1);
    }

    //绘制水银柱背景,包含水银柱底部圆
    drawBarBg(&painter);

    //绘制当前水银柱,包含水银柱底部圆
    drawBar(&painter);

    //绘制当前值
    drawValue(&painter);
}

void RulerTemp::drawBg(QPainter* painter)
{
    //绘制背景板，其实就是上个色
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPointF(0, 0), QPointF(0, height()));
    bgGradient.setColorAt(0.0, bgColorStart);
    bgGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void RulerTemp::drawBarBg(QPainter* painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barBgColor);

    int barX = targetX - barWidth / 2;
    int barY = space;
    QRectF barRect(barX, barY, barWidth, barHeight);

    int circleX = targetX - radius;
    //偏移 2 个像素,使得看起来边缘完整
    int circleY = height() - radius * 2 - 2;
    int circleWidth = radius * 2;
    QRectF circleRect(circleX, circleY, circleWidth, circleWidth);

    QPainterPath path;
    path.addRect(barRect);
    path.addEllipse(circleRect);
    path.setFillRule(Qt::WindingFill);
    painter->drawPath(path);
    painter->restore();
}

void RulerTemp::drawRuler(QPainter* painter, int type)
{
    painter->save();
    painter->setPen(lineColor);

    int barPercent = barWidth / 8;

    if (barPercent < 2)
    {
        barPercent = 2;
    }

    //绘制纵向标尺刻度
    double length = height() - 2 * space - 2 * radius;  //获得标尺长度;-4避免标尺在尾部出现断裂情况
    //计算每一度移动多少
    double increment = length / (maxValue - minValue);

    //长线条短线条长度
    int longLineLen = 10;
    int shortLineLen = 7;

    //绘制纵向标尺线 偏移 5 像素
    int offset = barWidth / 2 + 5;

    //左侧刻度尺需要重新计算
    if (type == 0) {
        offset = -offset;
        longLineLen = -longLineLen;
        shortLineLen = -shortLineLen;
    }

    double initX = targetX + offset;
    double initY = space + barPercent;
    QPointF topPot(initX, initY);
    QPointF bottomPot(initX, height() - 2 * radius - 0);
    painter->drawLine(topPot, bottomPot);   //画刻度的竖线

    //根据范围值绘制刻度值及刻度值
    QFont font;
    font.setPixelSize(tickFontSize);   //刻度数字的大小
    painter->setFont(font);
    for (int i = maxValue; i >= minValue; i = i - shortStep)  //线条是从上往下;从大往小绘制的
    {
        if (i % longStep == 0)
        {
            //绘制长线条
            QPointF rightPot(initX + longLineLen, initY);
            QPointF leftPot(initX, initY);
            painter->drawLine(leftPot, rightPot);

            //绘制文字
            QString strValue = QString("%1").arg((double)i, 0, 'f', precision);//precision决定在小数点后显示几位
            double fontHeight = painter->fontMetrics().height();
            QFontMetrics fm = QFontMetrics(painter->font()); //QFontMetrics计算字符串的高和宽
            int w = fm.horizontalAdvance(strValue);   //计算字符串的宽度

            if (type == 0)
            {
                QRect textRect(initX - 45, initY - fontHeight / 2, w, tickFontSize);
                painter->drawText(textRect, Qt::AlignRight, strValue);
            }
            else if (type == 1)
            {
                QRect textRect(initX + longLineLen + 5, initY - fontHeight / 2, w, tickFontSize);
                painter->drawText(textRect, Qt::AlignLeft, strValue);
            }
        }
        else
        {
            //绘制短线条
            QPointF rightPot(initX + shortLineLen, initY);
            QPointF leftPot(initX, initY);
            painter->drawLine(leftPot, rightPot);
        }

        initY += increment * shortStep;
    }

    painter->restore();
}

void RulerTemp::drawBar(QPainter* painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barColor);

    //计算在背景宽度的基础上缩小的百分比, 至少为 2
    int barPercent = barWidth / 8;
    int circlePercent = radius / 6;

    if (barPercent < 2) {
        barPercent = 2;
    }

    if (circlePercent < 2) {
        circlePercent = 2;
    }

    //标尺刻度高度
    double length = height() - 2 * space - 2 * radius;
    //计算每一度移动多少
    double increment = length / (maxValue - minValue);
    //计算标尺的高度
    int rulerHeight = height() - 2 * space - 2 * radius;

    int barX = targetX - barWidth / 2;
    int barY = rulerHeight - (currentValue - minValue) * increment;  //温度计柱高处没有水银部分的长度
    barRect = QRectF(barX + barPercent,
                     barY + barPercent,
                     barWidth - barPercent * 2,
                     barHeight + radius - barY);

    int circleX = targetX - radius;
    //偏移 2 个像素,使得看起来边缘完整
    int circleY = height() - radius * 2 - 2;
    int circleWidth = radius * 2 - circlePercent * 2;
    circleRect = QRectF(circleX + circlePercent,
                        circleY + circlePercent,
                        circleWidth,
                        circleWidth);

    QPainterPath path;
    path.addRect(barRect);
    path.addEllipse(circleRect);
    path.setFillRule(Qt::WindingFill);
    painter->drawPath(path);

    //绘制用户设定值三角号
    if (showUserValue)
    {
        if (tickPosition == TickPosition_Left || tickPosition == TickPosition_Both)
        {
            QPolygon pts;
            int offset = 15;
            double initX = targetX - (barWidth / 2 + 5);
            double initY = rulerHeight - (userValue - minValue) * increment;
            pts.append(QPoint(initX, initY));
            pts.append(QPoint(initX - offset, initY - offset / 2));
            pts.append(QPoint(initX - offset, initY + offset / 2));
            painter->setBrush(userValueColor);
            painter->drawPolygon(pts);
        }

        if (tickPosition == TickPosition_Right || tickPosition == TickPosition_Both)
        {
            QPolygon pts;
            int offset = 15;
            double initX = targetX + (barWidth / 2 + 5);
            double initY = rulerHeight - (userValue - minValue) * increment;
            pts.append(QPoint(initX, initY));
            pts.append(QPoint(initX + offset, initY - offset / 2));
            pts.append(QPoint(initX + offset, initY + offset / 2));
            painter->setBrush(userValueColor);
            painter->drawPolygon(pts);
        }
    }

    painter->restore();
}

void RulerTemp::drawValue(QPainter* painter)
{
    painter->save();

    QFont font;
    font.setPixelSize(circleRect.width() * 0.40);
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(circleRect, Qt::AlignCenter, QString("%1").arg(currentValue));

    painter->restore();
}

void RulerTemp::updateValue(int value)
{
    RulerTemp::currentValue = value;
    update();
}

void RulerTemp::updateValue(double value)
{
    RulerTemp::currentValue = value;
    update();
}

double RulerTemp::getMinValue() const
{
    return minValue;
}

double RulerTemp::getMaxValue() const
{
    return maxValue;
}

double RulerTemp::getValue() const
{
    return value;
}

int RulerTemp::getPrecision() const
{
    return precision;
}

int RulerTemp::getLongStep() const
{
    return longStep;
}

int RulerTemp::getShortStep() const
{
    return shortStep;
}

int RulerTemp::getSpace() const
{
    return space;
}

bool RulerTemp::getAnimation() const
{
    return animation;
}

double RulerTemp::getAnimationStep() const
{
    return animationStep;
}

bool RulerTemp::getShowUserValue() const
{
    return showUserValue;
}

double RulerTemp::getUserValue() const
{
    return userValue;
}

QColor RulerTemp::getUserValueColor() const
{
    return userValueColor;
}

QColor RulerTemp::getBgColorStart() const
{
    return bgColorStart;
}

QColor RulerTemp::getBgColorEnd() const
{
    return bgColorEnd;
}

QColor RulerTemp::getLineColor() const
{
    return lineColor;
}

QColor RulerTemp::getBarBgColor() const
{
    return barBgColor;
}

QColor RulerTemp::getBarColor() const
{
    return barColor;
}

RulerTemp::BarPosition RulerTemp::getBarPosition() const
{
    return BarPosition();
}

RulerTemp::TickPosition RulerTemp::getTickPosition() const
{
    return TickPosition();
}

QSize RulerTemp::sizeHint() const
{
    QSize size = parentWidget()->size();  //获得父对象，此处为QGridLayoout的大小
    return size;
}

QSize RulerTemp::minimumSizeHint() const
{
    QSize size = QSize(60,150);
    return size;
}

void RulerTemp::setRange(int minValue, int maxValue)
{
    RulerTemp::minValue = minValue;
    RulerTemp::maxValue = maxValue;
}

void RulerTemp::setMinValue(double minValue)
{
    RulerTemp::minValue = minValue;
}

void RulerTemp::setMaxValue(double maxValue)
{
    RulerTemp::maxValue = maxValue;
}

void RulerTemp::setValue(double value)
{
    if (RulerTemp::value == value)
        return;

    if (value > maxValue)
        RulerTemp::value = maxValue;
    else if (value < minValue)
        RulerTemp::value = minValue;
    else
    {
        RulerTemp::value = value;
    }

    if (RulerTemp::currentValue != RulerTemp::value)
    {
        timer->start(10);
    }
    emit valueChanged(value);

}

void RulerTemp::setValue(int value)
{
    if (RulerTemp::value == value)
        return;

    if (value > maxValue)
        RulerTemp::value = maxValue;
    else if (value < minValue)
        RulerTemp::value = minValue;
    else
    {
        RulerTemp::value = value;
    }

    if (RulerTemp::currentValue != RulerTemp::value)
    {
        timer->start(10);
    }

    emit valueChanged(value);
}

void RulerTemp::setCurValue(double v)
{
    RulerTemp::currentValue = v;
}

void RulerTemp::setCurValue(int v)
{
    RulerTemp::currentValue = v;
}

void RulerTemp::setPrecision(int precision)
{
    RulerTemp::precision = precision;
}

void RulerTemp::setLongStep(int longStep)
{
    RulerTemp::longStep = longStep;
}

void RulerTemp::setShortStep(int shortStep)
{
    RulerTemp::shortStep = shortStep;
}

void RulerTemp::setSpace(int space)
{
    RulerTemp::space = space;
}

void RulerTemp::setAnimation(bool animation)
{
    RulerTemp::animation = animation;
}

void RulerTemp::setAnimationStep(double animationStep)
{
    RulerTemp::animationStep = animationStep;
}

void RulerTemp::setShowUserValue(bool showUserValue)
{
    RulerTemp::showUserValue = showUserValue;
}

void RulerTemp::setUserValue(double userValue)
{
    RulerTemp::userValue = userValue;
}

void RulerTemp::setUserValue(int userValue)
{
    RulerTemp::userValue = userValue;
}

void RulerTemp::setUserValueColor(const QColor& userValueColor)
{
    RulerTemp::userValueColor = userValueColor;
}

void RulerTemp::setBgColorStart(const QColor& bgColorStart)
{
    RulerTemp::bgColorStart = bgColorStart;
}

void RulerTemp::setBgColorEnd(const QColor& bgColorEnd)
{
    RulerTemp::bgColorEnd = bgColorEnd;
}

void RulerTemp::setLineColor(const QColor& lineColor)
{
    RulerTemp::lineColor = lineColor;
}

void RulerTemp::setBarBgColor(const QColor& barBgColor)
{
    RulerTemp::barBgColor = barBgColor;
}

void RulerTemp::setBarColor(const QColor& barColor)
{
    RulerTemp::barColor = barColor;
}

void RulerTemp::setBarPosition(const BarPosition& barPosition)
{
    RulerTemp::barPosition = barPosition;
}

void RulerTemp::setTickPosition(const TickPosition& tickPosition)
{
    RulerTemp::tickPosition = tickPosition;
}

int RulerTemp::getTickFontSize()
{
    return tickFontSize;
}

void RulerTemp::setTickFontSize(int i)
{
    tickFontSize = i;
    update();
}


void RulerTemp::setRange(double minValue, double maxValue)
{
    RulerTemp::minValue = minValue;
    RulerTemp::maxValue = maxValue;
}
