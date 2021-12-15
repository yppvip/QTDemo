#ifndef GENERICDASHBOARD_H
#define GENERICDASHBOARD_H

#include <QPropertyAnimation>
#include <QWidget>
#include <QPainter>
#include <QtMath>
/* 通用仪表盘自定义控件 实现的功能
 * 1. 可设置范围值
 * 2. 可设置大刻度数量，小刻度数量
 * 3. 可设置开始旋转角度、结束旋转角度
 * 4. 可设置是否启用动画、动画特效及每刻度动画持续时间
 * 5. 可设置外圆背景、内圆背景、提示指针、刻度尺、刻度值、提示文字颜色
 * 6. 可设置三色刻度占用比例
 * 7. 自适应窗体拉伸、刻度尺和文字自动缩放
 */

/*改进的功能
 *允许输入输出小数
 *设置显示小数点后位数，最多为两位
 *速度字体大小和单位提示文本大小可单独设置:drawText
 *可设置字体:drawText
*/

class GenericDashBoard : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double minValue             READ getMinValue          WRITE setMinValue)
            Q_PROPERTY(double maxValue             READ getMaxValue          WRITE setMaxValue)
            Q_PROPERTY(double value                READ getValue             WRITE setValue)
            Q_PROPERTY(double curValue             READ getCurValue          WRITE updateValue)
            Q_PROPERTY(int animationStepTime    READ getAnimationStepTime WRITE setAnimationStepTime)
            Q_PROPERTY(int scaleMajor           READ getScaleMajor        WRITE setScaleMajor)
            Q_PROPERTY(int scaleMinor           READ getScaleMinor        WRITE setScaleMinor)
            Q_PROPERTY(int startAngle           READ getStartAngle        WRITE setStartAngle)
            Q_PROPERTY(int endAngle             READ getEndAngle          WRITE setEndAngle)
            Q_PROPERTY(int scalePercentage      READ getScalePercentage   WRITE setScalePercentage)
            Q_PROPERTY(QColor  scaleNumColor    READ getScaleNumColor     WRITE setScaleNumColor)
            Q_PROPERTY(QColor  outerCircleColor READ getOuterCircleColor  WRITE setOuterCircleColor)
            Q_PROPERTY(QColor  innerCircleColor READ getInnerCircleColor  WRITE setInnerCircleColor)
            Q_PROPERTY(QColor  scaleStartColor  READ getScaleStartColor   WRITE setScaleStartColor)
            Q_PROPERTY(QColor  scaleEndColor    READ getScaleEndColor     WRITE setScaleEndColor)
            Q_PROPERTY(QColor  pointerColor     READ getPointerColor      WRITE setPointerColor)
            Q_PROPERTY(QColor  textColor        READ getTextColor         WRITE setTextColor)
            Q_PROPERTY(QString suffixText       READ getSuffixText        WRITE setSuffixText)

public:
    explicit GenericDashBoard(QWidget *parent = nullptr);
    ~GenericDashBoard();
    int getMinValue()                   const;
        int getMaxValue()                   const;
        int getValue()                      const;
        int getAnimationStepTime()          const;
        int getScaleMajor()                 const;
        int getScaleMinor()                 const;
        int getStartAngle()                 const;
        int getEndAngle()                   const;
        QColor getScaleNumColor()           const;
        QColor getOuterCircleColor()        const;
        QColor getInnerCircleColor()        const;
        QColor getScaleStartColor()         const;
        QColor getScaleEndColor()           const;
        QColor getPointerColor()            const;
        QColor getTextColor()               const;
        QString getSuffixText()             const;
        QEasingCurve::Type getEasingCurve() const;
        double getScalePercentage()         const;

    public slots:
        void setRange(int minValue, int maxValue);                  // 设置范围值
        void setRange(double minValue, double maxValue);
        void setMinValue(int minValue);                             // 设置最小值
        void setMinValue(double minValue);
        void setMaxValue(int maxValue);                             // 设置最大值
        void setMaxValue(double maxValue);

        void setValue(int value);                                   // 设置目标值
        void setValue(double value);

        void setAnimationStepTime(int msec);                        // 设置每刻度动画持续时间

        void setScaleMajor(int scaleMajor);                         // 设置主刻度数量
        void setScaleMinor(int scaleMinor);                         // 设置小刻度数量

        void setAngleRange(int startAngle, int endAngle);           // 设备旋转角度范围
        void setStartAngle(int startAngle);                         // 设置开始旋转角度
        void setEndAngle(int endAngle);                             // 设置结束旋转角度

        void setScaleNumColor(const QColor& scaleNumColor);         // 设置刻度值颜色

        void setOuterCircleColor(const QColor& outerCircleColor);   // 设置外圆颜色
        void setInnerCircleColor(const QColor& innerCircleColor);   // 设置内圆颜色

        void setScalePercentage(double percentage);                 // 设置刻度百分比 【对应 m_scaleStartColor m_scaleEndColor】

        // 设置刻度两种颜色
        void setScaleStartColor(const QColor& scaleStartColor);
        void setScaleEndColor(const QColor& scaleEndColor);

        void setPointerColor(const QColor& pointerColor);       // 设置指针颜色
        void setTextColor(const QColor& textColor);             // 设置提示文本颜色
        void setSuffixText(const QString& string);              // 设置提示文字

        void setEasingCurve(QEasingCurve::Type type);           // 设置指针动画类型

        double getBoardFontSize();
        void   setBoardFontSize(double d);

        double getBoardSuffixSize();
        void setBoardSuffixSize(double d);

        QString getBoardFont();   //获取表盘文字的字体
        void setBoardFont(QString str);

        QString getSuffixFont();  //获取表盘提示内容的字体
        void setSuffixFont(QString str);

        int getNumDecimal();     //获取表盘数据显示时小数点后面的位数
        void setNumDecimal(int i); //设置表盘数据显示时小数点后面的位数;最多为两位
    protected:
        void paintEvent(QPaintEvent* event) override;
        void drawBackground(QPainter* painter);          // 绘制背景
        void drawScale(QPainter* painter);               // 绘制刻度
        void drawScaleNum(QPainter* painter);            // 绘制刻度值
        void drawPainterIndicator(QPainter* painter);    // 绘制指示器
        void drawText(QPainter* painter);                // 绘制提示文本

        double getCurValue() const;                         //获取当前值
        void updateValue(int value);                     // 更新表盘值        【主要在指针动画时使用】
        void updateValue(double value);

    signals:
        void valueChanged(double value);
        void valueChanged(int value);
        void finished();

    private:
        int m_radius = 0;                                    // 仪表盘半径
        QColor  m_outerCircleColor = QColor(172, 172, 172);  // 外圆背景色        【类比于手表金属外框】
        QColor  m_innerCircleColor = QColor(40, 40, 40);     // 内圆背景色        【类比于手表玻璃显示区域】
        QColor  m_scaleStartColor = QColor(84, 84, 84);      // 刻度开始部分颜色
        QColor  m_scaleEndColor = QColor(Qt::red);           // 刻度结束部分颜色   【如：没油、转速等告警提示】
        QColor  m_scaleNumColor = QColor(255, 255, 255);     // 刻度值颜色
        QColor  m_pointerColor = QColor(250, 50, 50);        // 指针颜色
        QColor  m_textColor = QColor(255, 255, 255);         // 提示文本颜色

        double m_curValue = 0;               // 表盘指针当前值     【主要在指针动画时使用】
        double m_value = 0;                  // 表盘指针最终指向的值
        double m_minValue = 0;               // 表盘最小值
        double m_maxValue = 240;             // 表盘最大值
        int m_startAngle = 45;            // 刻度盘起始角度
        int m_endAngle = 315;           // 刻度盘结束角度
        int m_scaleMajor = 10;            // 大刻度数量
        int m_scaleMinor = 5;             // 小刻度数量        【如：总刻度数量 = scaleMajor * scaleMinor】
        double m_scalePercentage = 0.8;   // 表盘刻度划分百分比 【对应 m_scaleStartColor m_scaleEndColor】
        QString m_suffixText = "Km/h";    // 提示文本后缀      【如：Km/h 等】

        double fontSize = 0.09;           //设置表盘上字体的大小;建议数值在0.09左右
        double suffixSize = 0.09;         //设置提示文本字体的大小;建议数值在0.09左右

        QString boardFont = "Consolas";   //设置表盘文字的字体
        QString suffixFont = "Consolas";  //设置单位提示文本的字体

        int numDecimal = 0;    //表盘数据显示时，小数点后面的位数

        QPropertyAnimation m_animation;   // 指针属性动画
        int m_animationStepTime = 50;     // 每刻度动画持续时间
        QEasingCurve::Type m_easingCurveType = QEasingCurve::OutQuad; // 指针动画缓和曲线类型

};

#endif // GENERICDASHBOARD_H
