#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSharedMemory>
#include <QBuffer>
#include <QDataStream>
#include <QLocalSocket>
#include <QProcess>
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
    void on_getMessageFromMemery_clicked();

    void on_sendMessageToMemery_clicked();

    void on_getMessageFromSocket_clicked();


private:
    Ui::Widget *ui;
    QSharedMemory *osshare;
    QLocalSocket *lsocket;
};
#endif // WIDGET_H
