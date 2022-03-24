#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

//自定义的日历

#include <QString>
#include <QWidget>
#include <QDate>
#include <QPushButton>
#include <QAbstractButton>
#include <QStackedWidget>
#include <QObject>
#include <QLabel>
#include <QFont>
#include <QPainter>
#include <QMouseEvent>

#define __WEEKWIDGETSTYLE           "color:#D3D8DF;"                   //星期的颜色
#define __DAYWIDGETSTYLE            "background-color:#1C1F28;"        //日期的背景颜色
#define __MONTHWIDGETSTYLE          "background-color:#1C1F28;"        //1-12 月的背景颜色
#define __YEARWIDGETSTYLE           "background-color:#1C1F28;"        //年份的背景颜色
#define __CALENDARBACKGROUND        "#1C1F28"                          //日历背景色
#define __CALENDARBORDER            "#000000"                          //日历borer
#define __CALENDARMARGIN            "#000000"                          //分割线颜色
#define __HOVERBACKGROUND           "#0096FF"                          //悬浮背景颜色
#define __HOVERCOLOR                "#D3D8DF"                          //悬浮文字颜色
#define __SELECTEDBACKGROUND        "#0096FF"                          //选中背景颜色
#define __SELECTEDCOLOR             "#D3D8DF"                          //选中文字颜色
#define __NORMALCOLOR               "#D3D8DF"                          //正常文字颜色
#define __WEEKENCOLOR               "#FF0000"                          //周末文字颜色
#define __NOTWORKINGBACKGROUND      "#555550"                          //非工作日背景颜色
#define __NOTWORKINGCOLOR           "#D3D8DF"                          //非工作日文字颜色
#define __NOTENABLECOLOR            "#6B737D"                          //非本月日期文字颜色

/*=========================================================*/

/*=========================================================*/

class DateIconButton : public QAbstractButton  //实现日历中不同日期的按钮类
{
    Q_OBJECT
public:
    enum DayType{
        normal,
        weekend,
        notworking,
        notenable,
        selected,
        hover,  //虚指
    };

    enum BtnType{
        DayBtn,
        MonthBtn,
        YearBtn
    };
    explicit DateIconButton(BtnType btnTy,QWidget *parent = nullptr);
    void setEnabled(bool value);
    void setType(DayType t,bool enable = true);
    void setPrevType(DayType t, bool enable = true);
    ~DateIconButton();

private:
    DayType type;  //当前的按钮类型
    DayType prevType;  //之前的按钮类型
    BtnType currentBtn;
    QSize selectedSize;



protected:
    void paintEvent(QPaintEvent *e);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void drawText(QPainter *painter,QColor color);
};

/*=========================================================*/

/*=========================================================*/
class TitleButton : public QAbstractButton   //实现年月选择栏的按钮类
{
    Q_OBJECT
public:
    enum DrawType{
        DrawText,
        DrawRightIcon,
        DrawLeftIcon,
    };
    explicit TitleButton(QWidget *parent = nullptr);
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
    void setType(DrawType ty);
    ~TitleButton();

private:
    DrawType type;
};

/*=========================================================*/

/*=========================================================*/

class CalendarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalendarWidget(QWidget *parent = nullptr);
    ~CalendarWidget();
    QDate getDate(){return date;}
    void setMinimumDate(QDate date){minDate = date; }
    void setMaximumDate(QDate date){maxDate = date; }
    void setSelectedDate(QDate tDate){date = tDate;}
    QDate selectedDate(){return date;}

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void wheelEvent(QWheelEvent * event);
    void showEvent(QShowEvent *event);

private:
    enum TitleType{
        DayType,
        MonthType,
        YearType
    };

    const int WeekCount = 7;
    const int RowCount = 5;
    const int minWidth = 220;
    const int minHeight = 220;
    const int margin = 2;
    const int titleSpace = 2;

    QDate date;
    QDate maxDate;
    QDate minDate;
    QList <DateIconButton *> calendarList;  //日期显示时的按钮集合
    QList <DateIconButton *> monthList;     //月份显示时的按钮集合
    QList <DateIconButton *> yearList;      //年显示时的按钮集合
    QList <QLabel *> weekList;
    TitleType type;
    TitleButton *titleBtn;
    TitleButton *nextBtn;
    TitleButton *prevBtn;
    int titleHeight;
    int weekHeight;
    int year;
    int month;
    int day;
    bool openDays;
    const int YearBeginCount = 5;

    QStackedWidget *stackedWidget;
    QWidget *dayWideget;
    QWidget *monthWidget;
    QWidget *yearWidget;

    QWidget *_getYearWidet();  //从堆叠窗口中获取指定的wiget
    QWidget *_getMonthWidget();
    QWidget *_getDayWidget();

    void initTitle();
    void initWeek();
    void initStackedWidget();
    void resizeTitle();
    void resizeWeek();
    void resizeStackedWidget();
    void resizeDays();
    void resizeMonth();
    void resizeYear();
    int addYear(int value);
    int addMonth(int value);
    void setTitleBtnText();

private slots:
    void titleClick();
    void prevClick();
    void nextClick();
    void monthClick();
    void yearClick();
    void daysClick();

signals:
    void clicked(QDate currentDate);

};

#endif // CALENDARWIDGET_H
