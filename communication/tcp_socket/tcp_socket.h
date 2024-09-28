#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include <QObject>
#include "QTcpSocket"
#include <QTimer>

class tcp_server;

class tcp_socket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit tcp_socket(QObject *parent = nullptr);
    ~tcp_socket();

public slots:
    void connectToServer(const QString &host, quint16 port);
    void disconnectFromServer();
    //void tryConnect();

    void onDisconnected();
    void tryConnect();

    void checkConnection();
    void onConnected();
    void onm_new_msg(); //获取新数据
    void onm_send_msg(QByteArray send_msg); //写数据
    void onm_close();
signals:
    void s_new_msg(QByteArray data);

private:
    QTcpSocket *socket;
    QTimer connectionChecker;
    const int reconnectInterval = 5000; // 5 seconds
};

#endif // TCP_SOCKET_H
