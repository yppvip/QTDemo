#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QPoint>
#include "datetimelineedit.h"
#include "selectcalendar.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    virtual void resizeEvent(QResizeEvent* event);

private:
    QWidget* centerWidget;
    QHBoxLayout* mainLayout;
    DateTimeLineEdit* dateTimeLineEdit;
    SelectCalendar* selectCalendar;
public slots:
    void slotUpdateSelectpos();
};
#endif // MAINWINDOW_H
