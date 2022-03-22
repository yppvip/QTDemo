#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QToolButton>
#include <QWidgetAction>
#include <QResizeEvent>
#include"datesegment.h"
#include "datesegmentline.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void slotOpenBtnClicked();
protected:
    virtual void resizeEvent(QResizeEvent* event);
private:
    DateSegmentLine* dateLineEdit;
    QHBoxLayout* mainLayout;
    QWidget* centerWidget;
    DateSegment* dateSegment;
};
#endif // MAINWINDOW_H
