#ifndef PUSHCOMBOX_H
#define PUSHCOMBOX_H

#include <QPushButton>
#include <QWidget>
#include <QListView>
#include <qstringlistmodel.h>
#include <QStandardItemModel>
#include <QModelIndex>

class PushCombox : public QPushButton
{
    Q_OBJECT
public:
    PushCombox(QWidget* parent = nullptr);
    ~PushCombox();
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    void addIconItem(QString);
    int currentIndex(){return  m_currindex;}
    void setCurrentIndex(int i);
signals:
    void    currentIndexChanged(int index);
public slots:
    void    on_clicked();
    void    on_showPopup();
private:
    QListView* listview;
    QStandardItemModel* model;
    QList<QString> iconList;
    int m_currindex;
    QWidget* widt;
    int parentwith;
    int parentheight;
};

#endif // PUSHCOMBOX_H
