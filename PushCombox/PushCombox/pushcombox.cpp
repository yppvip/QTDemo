#include "pushcombox.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QDesktopWidget>
PushCombox::PushCombox(QWidget *widget) : QPushButton(widget)
{
    m_currindex=0;
    m_currenttext="";
    widt=new QWidget(widget);  //widt的父对象是PushCombox的父对象
    listview=new QListView;
    QVBoxLayout *layout=new QVBoxLayout;
    layout->addWidget(listview);
    layout->setContentsMargins(0,0,0,0);
    widt->setLayout(layout);
    model=new QStringListModel;
    listview->setModel(model);
    listview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    widt->hide(); //这个就是弹出框，暂时让其隐藏
    //选中某个选项
    connect(listview,SIGNAL(clicked(QModelIndex)),SLOT(on_clicked()));
    //点击按钮，弹出选项框
    connect(this,SIGNAL(clicked(bool)),this,SLOT(on_showPopup()));
}

void PushCombox::addtextItem(QString str)
{
    QStringList list;
    list=model->stringList();
    list+=str;
    model->setStringList(list);
    this->setText(list.at(m_currindex));
}
void PushCombox::on_clicked()
{
    QStringList list;
    list=model->stringList();
    this->setText(list.at(listview->currentIndex().row())); //显示文字内容
    setCurrentIndex(listview->currentIndex().row());        //修改当前的索引
    setCurrentText(list.at(listview->currentIndex().row()));//修改当前的文本索引
    widt->hide();        //修改后就隐藏上拉选择框
}

void PushCombox::on_showPopup()
{
    if(!widt->isHidden())
    {
        widt->hide();
        return;
    }
    int height=20*listview->model()->rowCount();  //每一栏高20
    if(height > window()->height() - this->y())   //调整高度
        height=this->y();
    widt->resize(this->width(), height);
    widt->move(this->x(), this->y()-height);
    widt->show();
}

void PushCombox::addtextItems(QStringList list)
{
    model->setStringList(list);
    this->setText(list.at(m_currindex));
}

void PushCombox::setCurrentIndex(int i)
{
    if(i==m_currindex)
        return;
    m_currindex=i;
    QStringList list;
    list=model->stringList();
    this->setText(list.at(m_currindex));
    emit currentIndexChanged(m_currindex);
}

void PushCombox::setCurrentText(QString str)
{
    if(str==m_currenttext)
        return;
    m_currenttext=str;
    emit currentTextChanged(m_currenttext);
}
