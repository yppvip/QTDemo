#include "rulerbar.h"

RulerBar::RulerBar(QWidget *parent) : QWidget(parent)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
        this, &RulerBar::updateValue);
    setRange(0, 100);
    setValue(60.1);
    currentValue = 60.1;
    setPrecision(1);
    setLongStep(10);
    setShortStep(5);
    setSpace(25);
    setAnimation(true);
    setAnimationStep(2);
    setBgColorStart(QColor(255, 255, 255));
    setBgColorEnd(QColor(255, 255, 255));
    setLineColor(QColor(150, 20, 140));
    setBarBgColor(QColor(50, 200, 200));
    setBarColor(QColor(60, 240, 20));
}

RulerBar::~RulerBar()
{
    timer->deleteLater();
}

void RulerBar::updateValue()
{
    if (RulerBar::currentValue < RulerBar::value)
    {
        currentValue += 2;
        if (currentValue >= value)
        {
            currentValue = value;
            timer->stop();
        }
    }
    else if (RulerBar::currentValue > RulerBar::value)
    {
        currentValue -= 2;
        if (currentValue <= value)
        {
            currentValue = value;
            timer->stop();
        }
    }

    update();
}

void RulerBar::resizeEvent(QResizeEvent*)
{
}

void RulerBar::paintEvent(QPaintEvent*)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing |
                           QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制标尺
    drawRuler(&painter);
    //绘制柱状背景
    drawBarBg(&painter);
    //绘制柱状
    drawBar(&painter);
}

void RulerBar::drawBg(QPainter* painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPointF(0, 0), QPointF(0, height()));
    bgGradient.setColorAt(0.0, bgColorStart);
    bgGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void RulerBar::drawRuler(QPainter* painter)
{
    painter->save();
    painter->setPen(lineColor);

    //绘制纵向标尺线 30的长度为刻度尺文字的宽度
    double initX = space + 30;
    double initY = space;
    QPointF topPot(initX, initY);
    QPointF bottomPot(initX, height() - space);
    painter->drawLine(topPot, bottomPot);

    //绘制纵向标尺刻度
    double length = height() - 2 * space;
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    //长线条短线条长度
    int longLineLen = 10;
    int shortLineLen = 7;

    //根据范围值绘制刻度值及刻度值
    for (int i = maxValue; i >= minValue; i = i - shortStep)
    {
        if (i % longStep == 0)
        {
            QPointF leftPot(initX + longLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);

            QString strValue = QString("%1").arg((double)i, 0, 'f', precision);//precision决定在小数点后显示几位
            strValue = strValue + suffixStr;
            double fontWidth = painter->fontMetrics().width(strValue);
            double fontHeight = painter->fontMetrics().height();
            QPointF textPot(initX - fontWidth - 5, initY + fontHeight / 4);
            painter->drawText(textPot, strValue);
        }
        else
        {
            //两种不同的短线
            if (i % (longStep / 2) == 0)
            {
                shortLineLen = 7;
            }
            else
            {
                shortLineLen = 4;
            }

            QPointF leftPot(initX + shortLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);
        }

        initY += increment * shortStep;
    }

    painter->restore();
}

void RulerBar::setSuffixStr(QString s)
{
    suffixStr = s;
}

void RulerBar::drawBarBg(QPainter* painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    //20的长度为刻度尺文字的宽度 15为刻度尺到柱状图的宽度
    double initX = space + 30 + 15;
    QPointF topLeftPot(initX, space);
    QPointF bottomRightPot(width() - space, height() - space);
    barRect = QRectF(topLeftPot, bottomRightPot);

    painter->setBrush(barBgColor);
    painter->drawRect(barRect);
    painter->restore();
}

void RulerBar::drawBar(QPainter* painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    double barHeight = barRect.height();
    double increment = (double)barHeight / (maxValue - minValue);
    double initY = (currentValue - minValue) * increment;

    QPointF topLeftPot(barRect.topLeft().x(), barRect.bottomLeft().y() - initY);
    QPointF bottomRightPot(barRect.bottomRight());
    QRectF currentRect(topLeftPot, bottomRightPot);

    painter->setBrush(barColor);
    painter->drawRect(currentRect);
    painter->restore();
}

double RulerBar::getMinValue() const
{
    return minValue;
}

double RulerBar::getMaxValue() const
{
    return maxValue;
}

double RulerBar::getValue() const
{
    return value;
}

int RulerBar::getPrecision() const
{
    return precision;
}

int RulerBar::getLongStep() const
{
    return longStep;
}

int RulerBar::getShortStep() const
{
    return shortStep;
}

int RulerBar::getSpace() const
{
    return space;
}

bool RulerBar::getAnimation() const
{
    return animation;
}

double RulerBar::getAnimationStep() const
{
    return animationStep;
}

QColor RulerBar::getBgColorStart() const
{
    return bgColorStart;
}

QColor RulerBar::getBgColorEnd() const
{
    return bgColorEnd;
}

QColor RulerBar::getLineColor() const
{
    return lineColor;
}

QColor RulerBar::getBarBgColor() const
{
    return barBgColor;
}

QColor RulerBar::getBarColor() const
{
    return barColor;
}

QSize RulerBar::sizeHint() const
{
    QSize size = parentWidget()->size();
    if (size.width() > 100)
    {
      QSize  resize(100, size.height());
      return resize;
    }
    return size;
}

QSize RulerBar::minimumSizeHint() const
{
    return QSize(20,50);
}

void RulerBar::setRange(int minValue, int maxValue)
{
    RulerBar::minValue = minValue;
    RulerBar::maxValue = maxValue;
}

void RulerBar::setMinValue(double minValue)
{
    RulerBar::minValue = minValue;
}

void RulerBar::setMaxValue(double maxValue)
{
    RulerBar::maxValue = maxValue;
}

void RulerBar::setValue(double value)
{
    if (RulerBar::value != value)
    {
        RulerBar::value = value;
        emit valueChanged(value);
    }




    if (RulerBar::value != RulerBar::currentValue)
    {
        if (animation)
        {
            timer->start(10);
        }
        else
        {
            RulerBar::currentValue = RulerBar::value;
            update();
        }
    }
}

void RulerBar::setValue(int value)
{
    if (RulerBar::value != value)
    {
        RulerBar::value = value;
        emit valueChanged(value);
    }

    if (RulerBar::value != RulerBar::currentValue)
    {
        if (animation)
        {
            timer->start(10);
        }
        else
        {
            RulerBar::currentValue = RulerBar::value;
            update();
        }
    }
}

void RulerBar::setPrecision(int precision)
{
    RulerBar::precision = precision;
}

void RulerBar::setLongStep(int longStep)
{
    RulerBar::longStep = longStep;
}

void RulerBar::setShortStep(int shortStep)
{
    RulerBar::shortStep = shortStep;
}

void RulerBar::setSpace(int space)
{
    RulerBar::space = space;
}

void RulerBar::setAnimation(bool animation)
{
    RulerBar::animation = animation;

}

void RulerBar::setAnimationStep(double animationStep)
{
    RulerBar::animationStep = animationStep;
}

void RulerBar::setBgColorStart(const QColor& bgColorStart)
{
    RulerBar::bgColorStart = bgColorStart;
}

void RulerBar::setBgColorEnd(const QColor& bgColorEnd)
{
    RulerBar::bgColorEnd = bgColorEnd;
}

void RulerBar::setLineColor(const QColor& lineColor)
{
    RulerBar::lineColor = lineColor;
}

void RulerBar::setBarBgColor(const QColor& barBgColor)
{
    RulerBar::barBgColor = barBgColor;
}

void RulerBar::setBarColor(const QColor& barColor)
{
    RulerBar::barColor = barColor;
}

void RulerBar::setRange(double minValue, double maxValue)
{
    RulerBar::minValue = minValue;
    RulerBar::maxValue = maxValue;
}
