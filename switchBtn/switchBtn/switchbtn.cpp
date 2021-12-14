#include "switchbtn.h"

SwitchBtn::SwitchBtn(QWidget *parent) : QWidget(parent)
{
    m_space = 2;
    m_radius = 5;
    m_checked = false;
    m_showText = true;
    m_showCircle = false;
    m_animation = true;

    m_bgColorOn = QColor(21, 156, 119);
    m_bgColorOff = QColor(111, 122, 126);

    m_sliderColorOn = QColor(255, 255, 255);
    m_sliderColorOff = QColor(255, 255, 255);
    m_textColor = QColor(255, 255, 255);

    m_textOn = "开启";
    m_textOff = "关闭";

    m_step = 0;

    m_startX = 0;
    m_endX = 0;


    m_timer = new QTimer(this);
    m_timer->setInterval(30);  //设置该函数，在调用start函数时可以缺省参数
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slotUpdateValue()));
}


SwitchBtn::~SwitchBtn()
{
    m_timer->deleteLater();
}

void SwitchBtn::drawBackGround(QPainter* painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QColor bgColor = m_checked ? m_bgColorOn : m_bgColorOff;
    if (isEnabled())  //判断小部件是否启用， 启动的小部件才能接收鼠标和键盘事件
    {
        bgColor.setAlpha(60);  //设置透明度
    }

    painter->setBrush(bgColor);

    QRect rect(0, 0, width(), height());
    int side = qMin(width(), height());

    //左侧半圆
    QPainterPath path1;
    path1.addEllipse(rect.x(), rect.y(), side, side);

    //右侧半圆
    QPainterPath path2;
    path2.addEllipse(rect.width() - side, rect.y(), side, side);

    //中间的矩形
    QPainterPath path3;
    path3.addRect(rect.x() + side / 2, rect.y(), rect.width() - side, height());

    QPainterPath path = path1 + path2 + path3;
    painter->drawPath(path);

    //绘制文本

    //滑块直径
    int sliderWidth = qMin(height(), width()) - m_space * 2 - 5;
    if (m_checked)
    {
        QRect textRect(0, 0, width() - sliderWidth, height());  //开启时，滑块在右侧，从左侧绘制文字
        painter->setPen(QPen(m_textColor));
        painter->drawText(textRect, Qt::AlignCenter, m_textOn);

    }
    else
    {
        QRect textRect(sliderWidth, 0, width() - sliderWidth, height());
        painter->setPen(QPen(m_textColor));
        painter->drawText(textRect,Qt::AlignCenter, m_textOff);
    }
    painter->restore();
}

void SwitchBtn::drawSlider(QPainter* painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QColor color = m_checked ? m_sliderColorOn : m_sliderColorOff;

    painter->setBrush(QBrush(color));

    int sliderWidth = qMin(width(), height() - m_space);
    if (checked() && initFlag)
    {
        m_startX = width() - sliderWidth;
        initFlag = false;
    }

    QRect rect(m_space + m_startX, m_space, sliderWidth, sliderWidth);

    painter->drawEllipse(rect);

    painter->restore();
}

void SwitchBtn::paintEvent(QPaintEvent* event)
{
    //启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBackGround(&painter);

    //绘制滑块
    drawSlider(&painter);

    //计算步长
    m_step = width() / 10;


}

void SwitchBtn::mousePressEvent(QMouseEvent* event)
{
    m_checked = !m_checked;
    emit signalStatusChanged(m_checked);

    //计算步长
    m_step = width() / 10;

    //计算滑块X轴终点坐标
    if (m_checked)
    {
        m_endX = width() - height();
    }
    else
    {
        m_endX = 0;
    }

    //判断是否使用动画
    if (m_animation)
    {
        m_timer->start();
    }
    else
    {
        m_startX = m_endX;
        update();
    }
}

void SwitchBtn::resizeEvent(QResizeEvent *event)
{
    //计算滑块X轴终点坐标
    if (m_checked)
    {
        m_endX = width() - height();
    }
    else
    {
        m_endX = 0;
    }

        m_startX = m_endX;
        QWidget::resizeEvent(event);
}

void SwitchBtn::slotUpdateValue()
{
    if (m_checked)
    {
        if (m_startX < m_endX)
        {
            m_startX += m_step;
        }
        else
        {
            m_startX = m_endX;
            m_timer->stop();
        }
    }
    else
    {
        if (m_startX > m_endX)
        {
            m_startX -= m_step;
        }
        else
        {
            m_startX = m_endX;
            m_timer->stop();
        }
    }
    update();  //重绘
}



int SwitchBtn::space() const
{
    return m_space;
}


int SwitchBtn::radius() const
{
    return m_checked;
}

bool SwitchBtn::checked()  const
{
    return m_checked;
}

bool SwitchBtn::showText()  const
{
    return m_showText;
}

bool SwitchBtn::showCircel()  const
{
    return m_showCircle;
}

bool SwitchBtn::animation()   const
{
    return m_animation;
}

QColor SwitchBtn::bgColorOn()  const
{
    return m_bgColorOn;
}


QColor SwitchBtn::bgColorOff()   const
{
    return m_bgColorOff;
}

QColor SwitchBtn::sliderColorOn()  const
{
    return m_sliderColorOn;
}

QColor SwitchBtn::sliderColorOff()  const
{
    return m_sliderColorOff;
}

QColor SwitchBtn::textColor()  const
{
    return m_textColor;
}

QString SwitchBtn::textOn()  const
{
    return m_textOn;
}

QString SwitchBtn::textOff()  const
{
    return m_textOff;
}

int SwitchBtn::step()  const
{
    return m_step;
}

int SwitchBtn::startX() const
{
    return m_startX;
}

int SwitchBtn::endX()  const
{
    return m_endX;
}

void SwitchBtn::setSpace(int space)
{
    if (m_space != space)
    {
        m_space = space;
        update();
    }
}

void SwitchBtn::setRadius(int radius)
{
    if (m_radius != radius)
    {
        m_radius = radius;
        update();
    }
}

void SwitchBtn::setChecked(bool checked)
{
    if (m_checked != checked)
    {
        m_checked = checked;
        update();
    }
}

void SwitchBtn::setShowText(bool show)
{
    if (m_showText != show)
    {
        m_showText = show;
        update();
    }
}

void SwitchBtn::setShowCircle(bool show)
{
    if (m_showCircle != show)
    {
        m_showCircle = show;
        update();
    }
}


void SwitchBtn::setAnimation(bool ok)
{
    if (m_animation != ok)
    {
        m_animation = ok;
        update();
    }
}

void SwitchBtn::setBgColorOn(const QColor& color)
{
    if (m_bgColorOn != color)
    {
        m_bgColorOn = color;
        update();
    }
}

void SwitchBtn::setBgColorOff(const QColor& color)
{
    if (m_bgColorOff != color)
    {
        m_bgColorOff = color;
        update();
    }
}

void SwitchBtn::setSliderColorOn(const QColor& color)
{
    if (m_sliderColorOn != color)
    {
        m_sliderColorOn = color;
        update();
    }
}

void SwitchBtn::setSliderColorOff(const QColor& color)
{
    if (m_sliderColorOff != color)
    {
        m_sliderColorOff = color;
        update();
    }
}

void SwitchBtn::setTextColor(const QColor& color)
{
    if (m_textColor != color)
    {
        m_textColor = color;
        update();
    }
}

void SwitchBtn::setTextOn(const QString& text)
{
    if (m_textOn != text)
    {
        m_textOn = text;
        update();
    }
}

void SwitchBtn::setTextOff(const QString& text)
{
    if (m_textOff != text)
    {
        m_textOff = text;
        update();
    }
}
