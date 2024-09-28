#include "tcp_socket.h"
#include "QsLog/include/QsLog.h"
#include <QThread>


tcp_socket::tcp_socket(QObject *parent)
{
    connect(this,&tcp_socket::readyRead,this,&tcp_socket::onm_new_msg);
}

tcp_socket::~tcp_socket()
{
    this->disconnectFromHost();
    this->waitForDisconnected();
    delete socket;
}

void tcp_socket::connectToServer(const QString &host, quint16 port)
{
    this->connectToHost(host, port);
    QLOG_INFO() << "连接到：" << host ;
}

void tcp_socket::disconnectFromServer()
{
    this->disconnectFromHost();
}

void tcp_socket::onm_new_msg()
{
    QByteArray data = readAll();
    //QLOG_DEBUG() << QStringLiteral("socket接收 当前线程id : %1").arg(quintptr(QThread::currentThreadId()));
    emit s_new_msg(data);
}

void tcp_socket::onm_send_msg(QByteArray send_msg)
{
    //QLOG_DEBUG() << QStringLiteral("socket发送 当前线程id : %1").arg(quintptr(QThread::currentThreadId()));
    this->write(send_msg);
}

void tcp_socket::onm_close()
{
    this->abort();
    this->disconnect();
}


