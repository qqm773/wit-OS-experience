#include "threadwork.h"
int num1 =0;
int num = 0;
QMutex mutex;
ShowIncrease::ShowIncrease(QObject *parent) : QObject(parent)
{

}

void ShowIncrease::counting()
{
    qDebug()<<"自加线程开始工作,线程地址为"<<QThread::currentThread();
    int num = 0;
    while(1){
        emit CurNum(num++);
        if (num == 1e4) break;
        QThread::msleep(1);
    }
    qDebug()<<"自加线程工作完毕"<<QThread::currentThread();
}


ShowDecrease::ShowDecrease(QObject *parent) : QObject(parent)
{

}

void ShowDecrease::counting()
{
    qDebug()<<"自减线程开始工作,线程地址为"<<QThread::currentThread();
    int num = 0;
    while(1){
        emit CurNum(num--);
        if (num == 1e4) break;
        QThread::msleep(1);
    }
    qDebug()<<"自减线程工作完毕"<<QThread::currentThread();
}


Increase::Increase(QObject *parent) : QObject(parent)
{
    QMutexLocker locker(&mutex);
}

void Increase::counting()
{
    qDebug()<<"加线程开始工作,线程地址为"<<QThread::currentThread();
    int i=0;
    mutex.lock();
    while(i++<100){
        emit CurNum(num++);
        QThread::msleep(1);
    }
    mutex.unlock();
    emit done();
    qDebug()<<"加线程工作完毕"<<QThread::currentThread();
}


Decrease::Decrease(QObject *parent) : QObject(parent)
{
    QMutexLocker locker(&mutex);
}

void Decrease::counting()
{
    qDebug()<<"减线程开始工作,线程地址为"<<QThread::currentThread();
    int i=0;
    mutex.lock();
    while(i++<100){
        emit CurNum(num--);
        QThread::msleep(1);
    }
    mutex.unlock();
    emit done();
    qDebug()<<"减线程工作完毕"<<QThread::currentThread();
}

Increa::Increa(QObject *parent) : QObject(parent)
{

}

void Increa::counting()
{
    qDebug()<<"加线程开始工作,线程地址为"<<QThread::currentThread();
    while(1){
        emit CurNum(num++);
        if (num1 == 1e4) break;
        QThread::msleep(100);
    }

    qDebug()<<"加线程工作完毕"<<QThread::currentThread();
}


Decrea::Decrea(QObject *parent) : QObject(parent)
{

}

void Decrea::counting()
{
    qDebug()<<"减线程开始工作,线程地址为"<<QThread::currentThread();

    while(1){
        emit CurNum(num1--);
        if (num1 == 1e4) break;
        QThread::msleep(100);
    }

    qDebug()<<"减线程工作完毕"<<QThread::currentThread();
}


