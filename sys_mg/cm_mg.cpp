#include "cm_mg.h"
#include "QsLog/include/QsLog.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include "mainwindow.h"


#include "common.h"

//#define LOCAL_IP    ("192.168.41.106")
#define LOCAL_IP    ("192.168.7.237")


cm_mg::cm_mg(QObject *parent)
    : QObject{parent}
{
    m_server_socket = new tcp_socket(this);
    m_server_socket->connectToServer("47.97.180.36",40032);

#if(LOCAL_TEST)
    m_ctx = modbus_new_tcp("127.0.0.1",8000);
#else
    m_ctx = modbus_new_tcp(SLAVE_IP,SLAVE_PORT);
    m_ctx = modbus_new_tcp(SLAVE_IP_2,SLAVE_PORT_2);
#endif

    int ret = -1;
    if (NULL == m_ctx)
    {

        QLOG_INFO() << "新建modbus tcp失败";
    }
    else
    {
        int rc = modbus_set_slave(m_ctx,1);
        if(rc == -1)
        {
            QLOG_INFO() << "设置slave的地址失败";
             modbus_free(m_ctx);
        }
        else {

        }
    }

    connect(m_server_socket,&tcp_socket::readyRead,this,&cm_mg::tcp_rev);
}

cm_mg::~cm_mg()
{
    if(m_timer != nullptr)
        delete m_timer;

    //关联了parent  不需要手动删除
    //delete m_socket;
}

void cm_mg::onm_http_timer_callback()
{
    //disconnect(m_network_mg,&QNetworkAccessManager::finished,this,&cs_client::onm_recv);
    m_http_timer->stop();
    if(m_busy_status)
    {
        m_reply->abort();
        m_reply->deleteLater();
        m_busy_status = false;
    }

    //超时处理   暂不处理

}

bool cm_mg::col_room_temp()
{
    uint16_t buff[40];
    room_strc status;

    int ret = -1;
    ret = modbus_connect(m_ctx);
    if(ret == -1)
    {
        QLOG_INFO() << "room-1 连接salve错误";
    }
    else
    {
        if(modbus_read_registers(m_ctx,7990,35,buff) != -1)
        {

            status.room_name = "room-1";
            status.run_status = buff[0];
            status.cur_temp = buff[1];
            status.set_temp = buff[34];

            QLOG_INFO() << "room-1:成功读到 47990 47991 48024 的寄存器地址值 v1: " + QString::number(buff[0]) + " v2: " + QString::number(buff[1])
                    + " v3: " + QString::number(buff[34]);

            create_room_1_temp_js(status);
            // QJsonObject root_js;
            // QJsonArray datas;
            // QJsonObject values;
            // QString min = QDateTime::currentDateTime().toString("mm");
            // uint16_t min_int = (min.toUInt() / 5) *5;
            // QString cur_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:") +
            //         QString("%1").arg(min_int,2,10,QLatin1Char('0')) + ":00";
            // values.insert("cur_time",cur_time);
            // values.insert("room_id",status.room_name);
            // values.insert("run_status",status.run_status);
            // values.insert("cur_temp",status.cur_temp);
            // values.insert("set_temp",status.set_temp);


            // datas.append(values);
            // root_js.insert("datas",datas);

            QLOG_INFO() << "room-1 向服务器发送一条数据";
            //http_send(10000,"/write_room_temp",root_js);
        }
        else
        {
            QLOG_INFO() << "room-1 无法读取";
        }
        modbus_close(m_ctx);
    }

    return true;
}


bool cm_mg::col_room_2_temp()
{
    uint16_t buff[40];
    room_strc status;

    int ret = -1;
    ret = modbus_connect(m_ctx);
    if(ret == -1)
    {
        QLOG_INFO() << "room-2 连接salve错误";
        //        if(m_ctx !=NULL)


        //        modbus_free(m_ctx);
    }
    else
    {
        if(modbus_read_registers(m_ctx,7990,35,buff) != -1)
        {

            status.room_name = "room-2";
            status.run_status = buff[0];
            status.cur_temp = buff[1];
            status.set_temp = buff[34];

            QLOG_INFO() << "room-2:成功读到 47990 47991 48024 的寄存器地址值 v1: " + QString::number(buff[0]) + " v2: " + QString::number(buff[1])
                               + " v3: " + QString::number(buff[34]);

            create_room_2_temp_js(status);
            // QJsonObject root_js;
            // QJsonArray datas;
            // QJsonObject values;
            // QString min = QDateTime::currentDateTime().toString("mm");
            // uint16_t min_int = (min.toUInt() / 5) *5;
            // QString cur_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:") +
            //                    QString("%1").arg(min_int,2,10,QLatin1Char('0')) + ":00";
            // values.insert("cur_time",cur_time);
            // values.insert("room_id",status.room_name);
            // values.insert("run_status",status.run_status);
            // values.insert("cur_temp",status.cur_temp);
            // values.insert("set_temp",status.set_temp);


            // datas.append(values);
            // root_js.insert("datas",datas);
            QLOG_INFO() << "room-2 向服务器发送一条数据";
            //http_send(20000,"/write_room_temp",root_js);
        }
        else
        {
            QLOG_INFO() << "room-2 无法读取";
        }
        modbus_close(m_ctx);
    }

    return true;
}


bool cm_mg::get_root_jsonobj(QByteArray &data, QJsonObject &root_obj, uint32_t start_index)
{
    QJsonParseError err_pt;
    bool ok = false;
    int json_data_length = data.mid(16,11).toUInt(&ok);
    QJsonDocument root_doc = QJsonDocument::fromJson(data.mid(start_index,json_data_length),&err_pt);
    if(err_pt.error != QJsonParseError::NoError)
    {
        return false;
    }
    else {
        root_obj = root_doc.object();
    }
    return true;
}



void cm_mg::create_room_1_temp_js(room_strc status)
{
    // 创建JSON对象，用于构建消息结构
    QJsonObject root_js;
    QJsonObject data;
    QJsonObject values;

    // 向param对象中添加键值对
    //param.insert("select_desc","room_status");
    //values.insert("room_id",status.room_name);

    QString min = QDateTime::currentDateTime().toString("mm");
    uint16_t min_int = (min.toUInt() / 5) *5;
    QString cur_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:") +
                       QString("%1").arg(min_int,2,10,QLatin1Char('0')) + ":00";

    root_js.insert("room_id","room-1");
    root_js.insert("run_status",status.run_status);
    root_js.insert("cur_temp",status.cur_temp);
    root_js.insert("set_temp",status.set_temp);
    root_js.insert("cur_time",cur_time);

    // 将param和values对象作为键值对添加到root_js对象中
    //root_js.insert("data",data);
    //root_js.insert("values",values);

    // 发送创建消息到服务器
    send_cs_msg(root_js,CS_ROOM_TEMP_REQUEST);
}

void cm_mg::create_room_2_temp_js(room_strc status)
{
    // 创建JSON对象，用于构建消息结构
    QJsonObject root_js;
    QJsonObject data;
    QJsonObject values;

    // 向param对象中添加键值对
    //param.insert("select_desc","room_status");
    //values.insert("room_id",status.room_name);

    QString min = QDateTime::currentDateTime().toString("mm");
    uint16_t min_int = (min.toUInt() / 5) *5;
    QString cur_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:") +
                       QString("%1").arg(min_int,2,10,QLatin1Char('0')) + ":00";

    root_js.insert("room_id","room-2");
    root_js.insert("run_status",status.run_status);
    root_js.insert("cur_temp",status.cur_temp);
    root_js.insert("set_temp",status.set_temp);
    root_js.insert("cur_time",cur_time);

    // 将param和values对象作为键值对添加到root_js对象中
    //root_js.insert("data",data);
    //root_js.insert("values",values);

    // 发送创建消息到服务器
    send_cs_msg(root_js,CS_ROOM_TEMP_REQUEST);
}

void cm_mg::send_cs_msg(QJsonObject &root_js, QString cmd)
{
    QByteArray msg;
    QJsonDocument root_doc;

    root_doc.setObject(root_js);
    msg.append(root_doc.toJson(QJsonDocument::Compact));
    cs_communicate_encode(msg,cmd,"XXXX");
    //QLOG_INFO() << "发送--->" + QString(msg);
    //emit s_send_cs_msg(msg);
    m_server_socket->write(msg);
}

void cm_mg::cs_communicate_encode(QByteArray &buffer, QString cmd, QString status)
{
    int length = buffer.size();

    buffer.insert(0,CS_DEFAULT_HEARD);
    buffer.insert(8,cmd.toUtf8());
    buffer.insert(12,status.toUtf8());
    buffer.insert(16,QString("%1").arg(length,11,10,QLatin1Char('0')).toUtf8());
}

/*
void cm_mg::http_send(quint32 timeout, QString url, QJsonObject param)
{
    QNetworkRequest tmp_request;
    //地址 + （20000,"/write_room_temp",root_js）
    QUrl tmp_url(m_url_head + url);
    QUrlQuery tmp_url_quy;

    //如果上条指令未处理完
    if(m_busy_status)
    {
        //emit s_cs_request_busy();
        QLOG_INFO() << "http正在发送中";
        return ;
    }

    tmp_url_quy.addQueryItem("account",m_account);
    tmp_url_quy.addQueryItem("password",m_password);
    tmp_url.setQuery(tmp_url_quy);

    tmp_request.setUrl(tmp_url);

    //如果超过最大限制时
    if(timeout > m_max_timeout)
        m_http_timer->setInterval(m_max_timeout);
    else
        m_http_timer->setInterval(timeout);
    m_http_timer->setSingleShot(true);  //设置单次模式
    //开始记时
    m_http_timer->start();
    m_busy_status = true;

    tmp_request.setHeader(QNetworkRequest::ContentTypeHeader, ("charset=utf-8"));
    //发送
    m_reply = m_network_mg->post(tmp_request,common::js_to_qbytearray(param));
}

void cm_mg::http_recv(QNetworkReply *reply)
{
    int statusCode = 0;

    m_http_timer->stop();

    statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(reply->error() == QNetworkReply::NoError)
    {
        QJsonObject obj;
        //获取状态码

        //状态码处理
        if(statusCode == 200)
        {
            QLOG_INFO() << "服务器返回正常";
            //obj = common::qbytearray_to_js(reply->readAll());

            //emit s_cs_request_new_msg(reply->url().path(),obj);
        }
        else
        {
            QLOG_INFO() << "状态码异常";
        }
    }
    else
    {
        QLOG_INFO() << "服务器返回异常";
       // emit s_cs_request_err_status(reply->url().path(),QString::number(statusCode));
    }

    reply->abort();
    reply->deleteLater();
    m_busy_status = false;
}
*/


//15秒
void cm_mg::onm_timer_callback()
{
    static uint32_t t1 = 0;
    t1 ++;
    if(t1 >= 4)
    {
        //两间房
        col_room_temp();
        t1 = 0;
    }
}

//20秒
void cm_mg::onm_timer_callback_2()
{
    static uint32_t t1 = 0;
    t1 ++;
    if(t1 >= 4)
    {
        col_room_2_temp();
        t1 = 0;
    }
}

void cm_mg::onm_new_timer()
{
    //执行网络请求
    // m_network_mg = new QNetworkAccessManager;
    // connect(m_network_mg,&QNetworkAccessManager::finished,this,&cm_mg::http_recv);

    // m_http_timer = new QTimer();
    // connect(m_http_timer,&QTimer::timeout,this,&cm_mg::onm_http_timer_callback);

    m_timer = new QTimer();
    connect(m_timer,&QTimer::timeout,this,&cm_mg::onm_timer_callback);
    m_timer->start(15000);

    m_timer_2 = new QTimer();
    connect(m_timer_2,&QTimer::timeout,this,&cm_mg::onm_timer_callback_2);
    m_timer_2->start(20000);
}

void cm_mg::tcp_rev()
{
    // 设置超时时间为5000毫秒
    if (m_server_socket->waitForReadyRead(5000))
    {
        m_buff.append(m_server_socket->readAll());
        qDebug() << m_buff.size();
        while (m_buff.size() > 0)
        {
            QLOG_INFO() << "服务器返回正常";
        }
    }
    else
    {
        qDebug() << "读取数据超时";
    }
}
