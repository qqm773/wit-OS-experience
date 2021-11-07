#ifndef THREADWORK_H
#define THREADWORK_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>

class ShowIncrease : public QObject
{
    Q_OBJECT
public:
    explicit ShowIncrease(QObject *parent = nullptr);
    void counting();

signals:
    void CurNum(int num);
};


class ShowDecrease : public QObject
{
    Q_OBJECT
public:
    explicit ShowDecrease(QObject *parent = nullptr);
    void counting();

signals:
    void CurNum(int num);
};



class Increase : public QObject
{
    Q_OBJECT
public:
    explicit Increase(QObject *parent = nullptr);
    void counting();

signals:
    void CurNum(int num);
    void done();
};


class Decrease : public QObject
{
    Q_OBJECT
public:
    explicit Decrease(QObject *parent = nullptr);
    void counting();

signals:
    void CurNum(int num);
    void done();
};


class Increa : public QObject
{
    Q_OBJECT
public:
    explicit Increa(QObject *parent = nullptr);
    void counting();

signals:
    void CurNum(int num);
    void done();
};


class Decrea : public QObject
{
    Q_OBJECT
public:
    explicit Decrea(QObject *parent = nullptr);
    void counting();

signals:
    void CurNum(int num);
    void done();
};








#endif // THREADWORK_H
