#include <QDebug>
#include <QFont>
#include "TimerBar.h"

#define RECTY 60
#define CURSORHEIGTH 50
#define RECTHEIGH 10

TimeBar::TimeBar(QWidget *parent) :
    QWidget(parent),
    mCurrentDateTime(QDateTime::currentDateTime()),
    mSizeLevel(0)
{
    //设置ui样式
    initUi();
    setMouseTracking(true);

    initStepLevel(); //设置时间轴单位和像素步长的关系

    /*设置中间显示的时间游标Label和放缩等级按键的样式*/
    mMidDisplayLabel = new QLabel(this);
    mMidDisplayLabel->setFixedSize(QSize(150,24));
    mMidDisplayLabel->setAlignment(Qt::AlignCenter);
    mMidDisplayLabel->setStyleSheet("background:rgba(255,255,255,0);color:rgb(255,255,255);font:12px \"Microsoft YaHei\"");

    levelUpBtn->setStyleSheet("QPushButton{background:rgba(255,255,255,0); color:rgb(255,255,255); font-size:12px}"
                              "QPushButton:hover{font-size:14px}"
                              "QPushButton:pressed{font-size:10px}");

    levelDownBtn->setStyleSheet("QPushButton{background:rgba(255,255,255,0); color:rgb(255,255,255); font-size:12px}"
                                "QPushButton:hover{font-size:14px}"
                                "QPushButton:pressed{font-size:10px}");
    initSignalsAndSlots();

}

TimeBar::~TimeBar()
{

}

void TimeBar::setSizeLever(int level)
{
    if(level >= 0 && level <= mTotleLevel - 1){
        mSizeLevel = level;
        update();
    }
    else{
        qDebug() << "设置的显示系数有误";
    }
}

void TimeBar::setTimeRange(QVector<TimeRange> timeRange)
{
    mTimeRangeVec = timeRange;
    if(!timeRange.isEmpty()){
        mCurrentDateTime = mTimeRangeVec.at(0).startTime;
    }
    update();
}

void TimeBar::paintEvent(QPaintEvent *)
{
    // 绘制背景
    QPainter painter(this);
    painter.setBrush(QColor{50,50,50});
    painter.drawRect(rect());  //rect()会直接返回widget的范围

    //绘制时间刻度
    drawTimeScale(painter);

    //显示中间位置时间
    mMidDisplayLabel->setText(mCurrentDateTime.toString("yyyy-MM-dd hh:mm:ss"));
    mMidDisplayLabel->move(this->size().width()/2 - mMidDisplayLabel->width()/2 - 5, 10);  //没有使用布局直接使用move函数

    //绘制具体的时间数据
    drawTimeRange(painter);

    //绘制中央游标
    drawTimerCursor(painter);
}

void TimeBar::mousePressEvent(QMouseEvent *event)
{
    mIsPressed = true;
    mPressDateTime = mCurrentDateTime;
    mPressPointX = event->pos().x();
    QWidget::mousePressEvent(event);
}

void TimeBar::mouseReleaseEvent(QMouseEvent *event)
{
    mIsPressed = false;
    emit signalPlayTimeChanged(mCurrentDateTime);  //发送信号，调整视频播放的开端
    QWidget::mouseReleaseEvent(event);
}

void TimeBar::mouseMoveEvent(QMouseEvent *event)
{
    if(mIsPressed){
        int moveLength = event->pos().x()-mPressPointX;
        float secs = mStepVec.at(mSizeLevel).timeStep / mStepVec.at(mSizeLevel).pixelStep;  //计算每一像素对应的秒数
        mCurrentDateTime = mPressDateTime.addSecs(-secs * moveLength);
    }
    update();
}

void TimeBar::wheelEvent(QWheelEvent *event)   //滚轮事件处理
{
    if(event->delta() > 0){
        onLevelUpBtn();
    }
    else{
        onLevelDownBtn();
    }
    QWidget::wheelEvent(event);
}

void TimeBar::onLevelUpBtn()
{
    if(mSizeLevel < mTotleLevel - 1){
        mSizeLevel += 1;
    }

    update();
}

void TimeBar::onLevelDownBtn()
{
    if(mSizeLevel > 0){
        mSizeLevel -= 1;
    }

    update();
}

void TimeBar::initUi()
{
    if(objectName().isEmpty()){
        setObjectName("TimeBar");
    }
    resize(955,100);
    setMinimumSize(QSize(0,100));
    setMaximumSize(QSize(1920,100));
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName("verticalLayout");
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(10);
    horizontalLayout->setObjectName("horizontalLayout");
    horizontalSpacer = new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    levelDownBtn = new QPushButton(this);
    levelDownBtn->setObjectName("leveDownBtn");
    levelDownBtn->setMinimumSize(QSize(20,20));
    levelDownBtn->setMaximumSize(QSize(20,20));

    horizontalLayout->addWidget(levelDownBtn);

    levelUpBtn = new QPushButton(this);
    levelUpBtn->setObjectName("leveUpBtn");
    levelUpBtn->setMinimumSize(QSize(20,20));
    levelUpBtn->setMaximumSize(QSize(20,20));

    horizontalLayout->addWidget(levelUpBtn);

    verticalLayout->addLayout(horizontalLayout);

    verticalSpacer = new QSpacerItem(20,40,QSizePolicy::Minimum,QSizePolicy::Expanding);
    verticalLayout->addItem(verticalSpacer);

    this->setWindowTitle(QCoreApplication::translate("TimeBar","Form",nullptr));
    levelDownBtn->setText(QCoreApplication::translate("TimeBar","-",nullptr));
    levelUpBtn->setText(QCoreApplication::translate("TimeBar","+",nullptr));


}

void TimeBar::initStepLevel()
{
    mStepVec.append({12*60*60, 50.0});
    mStepVec.append({6*60*60,  60.0});
    mStepVec.append({2*60*60,  70.0});
    mStepVec.append({1*60*60,  80.0});
    mStepVec.append({30*60,    90.0});
    mStepVec.append({10*60,    100.0});
    mStepVec.append({5*60,     110.0});
    mStepVec.append({1*60,     120.0});
    mTotleLevel = mStepVec.size();
}

void TimeBar::initSignalsAndSlots()
{
    connect(levelDownBtn,&QPushButton::clicked,
            this,&TimeBar::onLevelDownBtn);

    connect(levelUpBtn,&QPushButton::clicked,
            this,&TimeBar::onLevelUpBtn);
}

void TimeBar::drawTimeScale(QPainter &painter)
{
    //绘制容纳时间的矩形
    painter.setPen(QColor{150,150,150});
    painter.drawRect(-1, RECTY, width() + 40, RECTHEIGH);  //绘制时间轴的矩形方框，两端超出范围是为了不显示竖直边框

    float pixelStep = mStepVec.at(mSizeLevel).pixelStep;
    int timeStep = mStepVec.at(mSizeLevel).timeStep;
    float secsPer = timeStep / pixelStep;  //每像素值对应的时间长度(秒)

    /* 计算时间轴最左侧的时间，
     * 也就是时间轴起点处的时间 */
    QDateTime timeBarStartTime = mCurrentDateTime.addSecs(-(this->width() / 2) * secsPer);
    int timeH = timeBarStartTime.time().hour();
    int timeM = timeBarStartTime.time().minute();
    int timeS = timeBarStartTime.time().second();
    int second = timeH * 3600 + timeM * 60 + timeS;   //计算进度条头部时间距离mCurrentDateTime的秒数

    int drawStartTime = (second / timeStep + 1) * timeStep - second;  //这里计算的是整数个时间步长多于当前时间长度的值，用于计算在左边界多远处画整数个时间轴
    int startPostion = drawStartTime / secsPer;  //计算对应的像素值

    QDateTime showStartTime = timeBarStartTime.addSecs(drawStartTime);
    QFont font{"\"Microsoft YaHei\"", 8, 57};
    int count = this->size().width() / pixelStep;   //计算需要绘制的刻度个数
    for(int i = 0; i <= count; ++i){
        float timeX = pixelStep * i + startPostion -10;  //计算绘图的刻度位置
        painter.setFont(font);
        painter.drawText(timeX, RECTY - 5, showStartTime.toString("hh:mm")); //绘制文字
        painter.drawLine(pixelStep * i + startPostion, RECTY - 1, pixelStep * i + startPostion, RECTY + 25); //垂直竖线
        showStartTime = showStartTime.addSecs(timeStep);
    }
}

void TimeBar::drawTimerCursor(QPainter &painter)    //绘制时间指示游标
{
    painter.setPen( QPen{QColor{255,0,0,200},2} );
    painter.drawLine(this->width() / 2 + 1, CURSORHEIGTH, this->width() / 2 + 1, 105); //绘制竖线
    QPolygonF cursorPolygon;
    cursorPolygon << QPointF(this->size().width() / 2,     CURSORHEIGTH)
                  << QPointF(this->size().width() / 2 + 4, CURSORHEIGTH - 4)
                  << QPointF(this->size().width() / 2 + 4, CURSORHEIGTH - 12)
                  << QPointF(this->size().width() / 2 - 4, CURSORHEIGTH - 12)
                  << QPointF(this->size().width() / 2 - 4, CURSORHEIGTH - 4);
    painter.setBrush(QColor{200, 200, 200});
    painter.setPen(QColor{200, 200, 200});
    painter.drawPolygon(cursorPolygon);
}

void TimeBar::drawTimeRange(QPainter &painter)
{
    for(int i = 0; i < mTimeRangeVec.count(); ++i){
        QDateTime sTime = mTimeRangeVec.at(i).startTime;
        QDateTime eTime = mTimeRangeVec.at(i).endTime;

        float pixelStep = mStepVec.at(mSizeLevel).pixelStep;  //获得像素步长
        int timeStep = mStepVec.at(mSizeLevel).timeStep;      //获得时间步长
        float secsper = timeStep / pixelStep;  //计算每个像素对应的秒数
        float sToCurrent = mCurrentDateTime.secsTo(sTime);
        float eToCurrent = mCurrentDateTime.secsTo(eTime);
        float length = eToCurrent - sToCurrent;

        int timeX = sToCurrent / secsper + this->width() / 2;  //绘制范围的像素起点
        int timeLen = length / secsper;                        //绘制范围的长度

        painter.setPen(QPen(Qt::darkYellow, 1, Qt::NoPen));
        painter.setBrush(QBrush(Qt::cyan, Qt::SolidPattern));
        painter.drawRect(timeX, RECTY + 1, timeLen, RECTHEIGH - 1);
    }
}









