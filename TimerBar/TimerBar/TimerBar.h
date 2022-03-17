#ifndef TimeBar_H
#define TimeBar_H

#include <QObject>
#include <QCoreApplication>
#include <QWidget>
#include <QTime>
#include <QLabel>
#include <QString>
#include <QDateTime>
#include <QMap>
#include <QVariant>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QPainter>
#include <QMouseEvent>
struct TimeRange   //时间轴范围,用于管理存在视频播放的范围数据
{
    QDateTime startTime;
    QDateTime endTime;
};
class TimeBar : public QWidget
{
    Q_OBJECT
    struct TimeForDistance //储存时间步长和像素步长之间的关系
    {
        int timeStep;  //以秒为单位
        float pixelStep;
    };

public:

    explicit TimeBar(QWidget *parent = nullptr);
    ~TimeBar();

    void setSizeLever(int lever);   //设置步长和像素之间的关系等级
    QDateTime getCurrentTime(){return mCurrentDateTime;}
    void setTimeRange(QVector<TimeRange> timeRange);  //设置有视频的时间范围

protected:
    virtual void paintEvent(QPaintEvent*);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void wheelEvent(QWheelEvent* event);

public slots:
    void onLevelUpBtn();   //等级提高按钮按下("+"按钮)，刻度精度变高，时间轴上表示的总范围变小
    void onLevelDownBtn(); //等级降低按钮按下("-"按钮),刻度精度变低，时间轴上表示的总范围变大
private:
    void initUi();     //初始化ui界面
    void initStepLevel();  //初始化mStepVec数组
    void initSignalsAndSlots();
    void drawTimeScale(QPainter& painter);
    void drawTimerCursor(QPainter& painter);
    void drawTimeRange(QPainter& painter);

private:
    QDateTime mPressDateTime;   //用于得到鼠标按下滑动时间轴调整的时间
    QDateTime mCurrentDateTime; //游标当前指向的时间
    QLabel* mMidDisplayLabel;  //中央显示Label控件
    bool mIsPressed;
    int mPressPointX;

    QVector<TimeForDistance> mStepVec;
    int mTotleLevel;
    int mSizeLevel;
    QVector<TimeRange> mTimeRangeVec;   //可能存在多个不连续的时间范围，通过该变量管理

    /**********ui设计部分**********/
    QVBoxLayout* verticalLayout;
    QHBoxLayout* horizontalLayout;
    QSpacerItem* horizontalSpacer;
    QPushButton* levelDownBtn;
    QPushButton* levelUpBtn;
    QSpacerItem* verticalSpacer;


};

#endif // TimeBar_H
