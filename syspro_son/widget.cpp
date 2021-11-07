#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    osshare = new QSharedMemory;
    osshare->setKey("made by xuwei");
    this->setWindowTitle("OSProcess Small");
    lsocket = new QLocalSocket(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_getMessageFromMemery_clicked()
{
//    if (!osshare->isAttached()) {
//        osshare->attach();
//        return;
//    }
    if (!osshare->attach()) {
        ui->readtext->setText("attach Error");
        return;
    }
    QBuffer osbuf;
    QDataStream in(&osbuf);
    QString osmessage;
    osshare->lock();
    osbuf.setData((char*)osshare->constData(),osshare->size());
    osbuf.open(QBuffer::ReadWrite);
    in >> osmessage;
    osshare->unlock();
    osshare->detach();
    osbuf.destroyed();
    ui->readtext->setText(osmessage);

}


void Widget::on_sendMessageToMemery_clicked()
{
    //将内存段与进程分离
    osshare->detach();
    //缓冲区
    QBuffer osbuf;
    //打开缓冲
    osbuf.open(QBuffer::ReadWrite);
    //将缓冲区和数据流连接
    QDataStream out(&osbuf);
    //将数据加载到缓冲区
    out<<ui->readtext->toPlainText();
    int size = osbuf.size();
    //定量创建共享内存段
    if (!osshare->create(size)) return;
    osshare->lock();
    char *to = (char*)osshare->data();
    const char *from = osbuf.data().data();
    memcpy(to,from,qMin(osshare->size(),size));
    osbuf.destroyed();
    osshare->unlock();
}

void Widget::on_getMessageFromSocket_clicked()
{
    lsocket->connectToServer("xuwei");
    if(!lsocket->isReadable()) {
        ui->readtext->setText("Disconnect");
        return;
    }
    QString msg = lsocket->readAll();
    ui->readtext->setText(msg);
}


