#include "pushcombox.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QDesktopWidget>
PushCombox::PushCombox(QWidget *widget) : QPushButton(widget)
{
    setIconSize(QSize(25,25));
    m_currindex=0;
    widt=new QWidget(widget);  //widt的父对象是PushCombox的父对象
    listview=new QListView;
    listview->setViewMode(QListView::IconMode);  //设置为加载图标的模式
    listview->setIconSize(QSize(25,25));
    listview->setGridSize(QSize(30,30));
    listview->setResizeMode(QListView::Adjust);
    listview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QVBoxLayout *layout=new QVBoxLayout;
    layout->addWidget(listview);
    layout->setContentsMargins(0,0,0,0);
    widt->setLayout(layout);
    model = new QStandardItemModel;
    listview->setModel(model);
    listview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    widt->hide(); //这个就是弹出框，暂时让其隐藏
    //选中某个选项
    connect(listview,SIGNAL(clicked(QModelIndex)),SLOT(on_clicked()));
    //点击按钮，弹出选项框
    connect(this,SIGNAL(clicked(bool)),this,SLOT(on_showPopup()));
}

PushCombox::~PushCombox()
{
    QList<QStandardItem *> clearList;
    clearList = model->takeColumn(0);
    qDeleteAll(clearList);

    model->clear();
    model->deleteLater();
    listview->deleteLater();
}


void PushCombox::addIconItem(QString path)
{
    QStandardItem * item;
    item = new QStandardItem(QIcon(path),"");
    model->appendRow(item);
    iconList.append(path);

    this->setIcon(QIcon(iconList.at(m_currindex)) );

}
void PushCombox::on_clicked()
{
    this->setIcon( QIcon(iconList.at(listview->currentIndex().row())) );

    setCurrentIndex(listview->currentIndex().row());      //修改当前的索引,会发送消息
    widt->hide();        //修改后就隐藏上拉选择框
}

void PushCombox::on_showPopup()
{
    if(!widt->isHidden())
    {
        widt->hide();
        return;
    }
    int height=31*listview->model()->rowCount();  //每一栏高20
    if(height > window()->height() - this->y())   //调整高度
        height=this->y();
    widt->resize(this->width(), height);
    widt->move(this->x(), this->y()-height);
    widt->show();
}


void PushCombox::setCurrentIndex(int i)
{
    if(i==m_currindex)
        return;
    m_currindex=i;
    this->setIcon( QIcon(iconList.at(m_currindex)) );
    emit currentIndexChanged(m_currindex);
}
