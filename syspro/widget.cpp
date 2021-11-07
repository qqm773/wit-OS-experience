#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("OSProcess BIG");

    // 进程创建及通信
    p = new QProcess(this );
    // 共享内存
    osshare = new QSharedMemory(this);
    osshare->setKey("made by xuwei");
    // LocalSocket/LocalServer
    lserver = new QLocalServer(this);
    lsocket = new QLocalSocket(this);
    ui->connectlabel->setPixmap(QPixmap(":/1").scaled(40,40));
    connect(lserver,&QLocalServer::newConnection,this,[=](){
        ui->connectlabel->setPixmap(QPixmap(":/2").scaled(40,40));
        connect(lsocket,&QLocalSocket::disconnected,this,[=](){
            lsocket->close();
            ui->connectlabel->setPixmap(QPixmap(":/1").scaled(40,40));
        });

    });




    // 多线程创建
    qDebug()<<QThread::currentThread();
    QThread* thread1 = new QThread;thread1->start();
    QThread* thread2 = new QThread;thread2->start();
    QThread* thread3 = new QThread;thread3->start();
    QThread* thread4 = new QThread;thread4->start();
    QThread* thread5 = new QThread;thread5->start();
    QThread* thread6 = new QThread;thread6->start();
    ShowIncrease* showin = new ShowIncrease;
    ShowDecrease* showde = new ShowDecrease;
    showin->moveToThread(thread1);
    showde->moveToThread(thread2);
    Increase* in = new Increase;
    Decrease* de = new Decrease;
    in->moveToThread(thread3);
    de->moveToThread(thread4);
    Increa* increa = new Increa;
    Decrea* decrea = new Decrea;
    increa->moveToThread(thread5);
    decrea->moveToThread(thread6);

    // 信号槽连接
    connect(ui->createthread,&QPushButton::clicked,showin,&ShowIncrease::counting);
    connect(ui->createthread,&QPushButton::clicked,showde,&ShowDecrease::counting);
    connect(showin,&ShowIncrease::CurNum,this,[=](int num){
        ui->label_1->setNum(num);
    });
    connect(showde,&ShowDecrease::CurNum,this,[=](int num){
        ui->label_2->setNum(num);
    });
    connect(in,&Increase::CurNum,this,[=](int num){
        ui->label_3->setNum(num);
    });
    connect(de,&Decrease::CurNum,this,[=](int num){
        ui->label_3->setNum(num);
    });
    connect(increa,&Increa::CurNum,this,[=](int num){
        ui->label_4->setNum(num);
    });
    connect(decrea,&Decrea::CurNum,this,[=](int num){
        ui->label_4->setNum(num);
    });
    connect(ui->mutex,&QPushButton::clicked,in,&Increase::counting);
    connect(ui->mutex,&QPushButton::clicked,de,&Decrease::counting);
    connect(in,&Increase::done,de,&Decrease::counting);
    connect(de,&Decrease::done,in,&Increase::counting);
    connect(ui->unmutex,&QPushButton::clicked,increa,&Increa::counting);
    connect(ui->unmutex,&QPushButton::clicked,decrea,&Decrea::counting);
    connect(ui->closethread,&QPushButton::clicked,this,[=](){
        delete showin;
        delete showde;
        delete in;
        delete de;
        delete increa;
        delete decrea;
        thread1->terminate();
        thread2->terminate();
        thread3->terminate();
        thread4->terminate();
        thread5->terminate();
        thread6->terminate();
    });
}

Widget::~Widget()
{
    delete ui;
}


// 将文本框中的进程打开
void Widget::on_openpro_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,"Open_EXE","D:\\QTproject","EXE (*.exe)");
    if (path.isEmpty()) { return; }
    ui->text->setText(path);
    p->startDetached(path); //start()子进程随父进程消亡  startDetached()子进程可以单独存活
}

//将信息发送到共享内存段中
void Widget::on_sendmessage_clicked()
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
    out<<ui->text->toPlainText();
    int size = osbuf.size();
    //定量创建共享内存段
    if (!osshare->create(size)) return;
    //将内存段上锁，防止其他进程访问
    osshare->lock();

    //数据从缓冲区复制到内存段中
    char *to = (char*)osshare->data();
    const char *from = osbuf.data().data();
    memcpy(to,from,qMin(osshare->size(),size));

    //将内存段解锁，允许其他进程访问
    osshare->unlock();
    osbuf.destroyed();
}

// 从共享内存段中获取信息
void Widget::on_getMessage_clicked()
{
    //将内存段和进程连接
    if (!osshare->isAttached()) {
        osshare->attach();
        return;
    }
//    if (!osshare->attach()) {
//        ui->text->setText("attach Error");
//        return;
//    }
    QBuffer osbuf;
    QDataStream in(&osbuf);
    QString osmessage;
    //将内存段上锁，防止其他进程访问
    osshare->lock();

    //数据从内存段中读入缓冲区
    osbuf.setData((char*)osshare->constData(),osshare->size());
    osbuf.open(QBuffer::ReadWrite);
    in >> osmessage;
    //将内存段解锁，允许其他进程访问
    osshare->unlock();
    //将内存段与进程分离
    osshare->detach();

    osbuf.destroyed();
    ui->text->setText(osmessage);
}


void Widget::on_locserver_clicked()
{
    lserver->listen("xuwei");
    if(!lserver->isListening()) {
        ui->text->setText("server doesn`t run");
        return;
    }
    QString msg = ui->text->toPlainText();
    connect(lserver,&QLocalServer::newConnection,this,[=](){
        lsocket = lserver->nextPendingConnection();
    });

    lsocket->write(msg.toUtf8());
}


void Widget::on_disconnect_clicked()
{
    lsocket->abort();
}

