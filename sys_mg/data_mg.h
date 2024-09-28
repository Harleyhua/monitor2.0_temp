#ifndef DATA_MG_H
#define DATA_MG_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include "communication/tcp_socket/tcp_socket.h"

class data_mg : public QObject
{
    Q_OBJECT
public:
    explicit data_mg(QObject *parent = nullptr);
    ~data_mg();
    QTimer m_timer; //定时处理



};

#endif // DATA_MG_H
