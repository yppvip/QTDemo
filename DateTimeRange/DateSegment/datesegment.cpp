#include "datesegment.h"

DateSegment::DateSegment(QWidget *parent) : QWidget(parent),
    startDateTime(QDateTime::currentDateTime()),
    endDateTime(QDateTime::currentDateTime())
{
    startDateTime.setTime(QTime(0, 0, 0));
    endDateTime.setTime(QTime(18, 0, 0));

    startPanel = new DateTimePanel();
    endPanel = new DateTimePanel();
    startPanel->initTime(0, 0, 0);
    startPanel->initLabelText("开始时间");
    endPanel->initTime(18, 0, 0);
    endPanel->initLabelText("结束时间");
    panelLayoutHBox = new QHBoxLayout;
    panelLayoutHBox->addWidget(startPanel);
    panelLayoutHBox->addWidget(endPanel);
    panelLayoutHBox->setContentsMargins(0, 0, 0, 0);
    panelLayoutHBox->setSpacing(0);

    dayLabel = new QLabel(QString("今天:%1").
                          arg(QDateTime::currentDateTime().
                              toString("yyyy-MM-dd")));

    cancelBtn = new QPushButton("取消");
    sureBtn = new QPushButton("确定");
    dayLayoutHBox = new QHBoxLayout();
    dayLayoutHBox->addWidget(dayLabel);
    dayLayoutHBox->addStretch();
    dayLayoutHBox->addWidget(cancelBtn);
    dayLayoutHBox->addWidget(sureBtn);

    segmentLayoutVBox = new QVBoxLayout();

    segmentLayoutVBox->addLayout(panelLayoutHBox);
    segmentLayoutVBox->addLayout(dayLayoutHBox);
    segmentLayoutVBox->setContentsMargins(0, 0, 0, 0);
    segmentLayoutVBox->setSpacing(0);
    setLayout(segmentLayoutVBox);
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    //必须限制控件的大小，不然会导致在父控件中被压制的不可显示
    setMaximumSize(450,300);
    setMinimumSize(450,300);
    hide();


    connect(sureBtn, &QPushButton::clicked,
            this,&DateSegment::slotSureBtnClicked);
    connect(cancelBtn, &QPushButton::clicked,
            this,&DateSegment::slotCancelBtnClicked);
}

DateSegment::~DateSegment()
{

}

void DateSegment::slotCancelBtnClicked()
{
    hide();
}

void DateSegment::slotSureBtnClicked()
{
    QDateTime start = startPanel->getDateTime();
    QDateTime end = endPanel->getDateTime();

    if(start.secsTo(end) > 0){
        startDateTime = start;
        endDateTime = end;

        emit signalUpdate(startDateTime,endDateTime);
        hide();
    }
    return;
}

void DateSegment::slotUpdate()
{
    if(isHidden()){
        QString str;
        str = "今天:" + QDateTime::currentDateTime().
                toString("yyyy-MM-dd");
        startPanel->updateInfo();
        endPanel->updateInfo();
        show();
    }
}
