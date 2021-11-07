#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProcess>
#include <QSharedMemory>
#include <QFileDialog>
#include <QBuffer>
#include <QDataStream>
#include <QThread>
#include <threadwork.h>
#include <QDebug>
#include <QtNetwork/QLocalSocket>
#include <QtNetwork/QLocalServer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:
    void on_openpro_clicked();

    void on_sendmessage_clicked();

    void on_getMessage_clicked();

    void on_locserver_clicked();

    void on_disconnect_clicked();

private:
    Ui::Widget *ui;
    QProcess *p;
    QSharedMemory *osshare;
    QLocalServer *lserver;
    QLocalSocket *lsocket;
};
#endif // WIDGET_H
