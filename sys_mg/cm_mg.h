#ifndef CM_MG_H
#define CM_MG_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include "communication/tcp_socket/tcp_socket.h"
#include "libmodbus/modbus.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>

#define CS_HEAD_FORMAT_LENGTH 27
#define CS_OK                 "2100"   //正常返回
#define CS_HEAD_ERROR         "2101"   //固定头错误
#define CS_STATUS_ERROR       "2102"   //指令错误
#define CS_JSON_FORMAET_ERROR "2103"   //JSON格式错误
#define CS_USE_DB_ERROR       "2104"   //数据库访问异常
#define CS_ERROR              "2105"   //无区分的错误返回

#define CS_DEFAULT_HEARD        "HEAD55AA"


#define CS_ROOM_TEMP_REQUEST "1007"
#define CS_ROOM_TEMP_RESPON  "4002"

#define LOCAL_TEST  0  //0 正式采集模式  1 测试采集模式

//room-1
#define SLAVE_IP    ("192.168.31.5")
#define SLAVE_PORT     8000
//room-2
#define SLAVE_IP_2   ("192.168.31.6")
#define SLAVE_PORT_2    8000

typedef struct
{
    QString room_name;
    //bool run_status;//运行情况
    int run_status;
    uint16_t cur_temp;  //实时温度
    uint16_t set_temp;  //当前温度
}room_strc;


class cm_mg : public QObject
{
    Q_OBJECT
public:
    explicit cm_mg(QObject *parent = nullptr);
    ~cm_mg();

    QByteArray m_buff;
    tcp_socket *m_server_socket;
    modbus_t* m_ctx = NULL;

    QByteArray cache;

    QTimer *m_timer = nullptr; //定时处理
    QTimer *m_timer_2 = nullptr;
    QTimer *m_http_timer =nullptr;

    QNetworkReply * m_reply = nullptr;
    bool m_busy_status = false;
    QNetworkAccessManager *m_network_mg = nullptr;  //网络数据管理对象
    //QString m_url_head = "http://localhost:38700";
#if LOCAL_TEST
    //QString m_url_head = "http://1.117.152.46:38700";
    QString m_url_head = "http://localhost:38700";
#else
    //QString m_url_head = "http://47.97.180.36:38700";
    QString m_url_head = "http://localhost:38700";
#endif
    quint32 m_max_timeout = 15000;  //最大超时时间  ms
    QString m_account = "aging_room1";
    QString m_password = "123456";

    void onm_http_timer_callback();

    bool col_room_temp();
    bool col_room_2_temp();
    bool analysis(QByteArray &data);
    bool get_root_jsonobj(QByteArray &data,QJsonObject &root_obj,uint32_t start_index = 27); //json数据是否正常

    void create_room_1_temp_js(room_strc status);
    void create_room_2_temp_js(room_strc status);
    void send_cs_msg(QJsonObject &obj,QString cmd);
    void cs_communicate_encode(QByteArray &buffer,QString cmd,QString status);   //客户端协议封包
    void tcp_rev();

    //2.0
    // void http_send(quint32 timeout, QString url, QJsonObject param);
    // void http_recv(QNetworkReply *reply);
public slots:
    void onm_timer_callback();
    void onm_timer_callback_2();
    void onm_new_timer();

signals:
    void s_send_cs_msg(QByteArray msg);
};

#endif // CM_MG_H
