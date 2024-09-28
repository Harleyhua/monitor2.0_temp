#ifndef SYS_MG_H
#define SYS_MG_H

#include <QObject>
#include <QThread>




class sys_mg : public QObject
{
    Q_OBJECT
public:
    explicit sys_mg(QObject *parent = nullptr);
    ~sys_mg();
    void start();
private:
    QThread m_sys_thread;
    QThread m_socket_thread;
    QThread m_data_analysis_thread;
};

#endif // SYS_MG_H
