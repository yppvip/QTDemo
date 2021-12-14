#ifndef WHIRLBTN_H
#define WHIRLBTN_H

#include <QColor>
#include <QImage>
#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QPainterPath>
#include <QEasingCurve>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QtMath>

#define WhirlBtnWidth  120
#define WhirlBtnHeight 130

class WhirlBtn : public QWidget
{
    Q_OBJECT
public:
    explicit WhirlBtn(QWidget *parent = nullptr);

    ~WhirlBtn();
        void paintEvent(QPaintEvent* event);
        void setDegree(int deg);
        int getDegree();

        //在指定位置设定文字
        void SetLeftStr(QString str);
        void SetMidStr(QString str);
        void SetRightStr(QString str);

        QString leftStr = "启动";
        QString midStr = "0";
        QString rightStr = "停止";

    signals:
        void updateDegree();
    protected:
        void mousePressEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void mouseToPosion(QMouseEvent* event);
        QSize sizeHint() const;
        QSize minimumSizeHint() const;

    private:
        int degree;

};

#endif // WHIRLBTN_H
