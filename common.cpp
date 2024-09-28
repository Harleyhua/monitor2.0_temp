#include "common.h"
#include <QRegExp>
#include <QHostInfo>
#include <QDateTime>


common::common(QObject *parent)
    : QObject{parent}
{

}
bool common::is_ip_valid(QString ip)
{
    //ip校验正则
    QRegExp regExpIP("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])[\\.]){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])");
    return regExpIP.exactMatch(ip);
}

bool common::is_port_valid(QString port)
{
    bool ret = false;
    int n_port = 70000;
    n_port = port.toInt(&ret,10);

    if(n_port >=0 && n_port <= 65535)
        return true;

    return false;
}

bool common::is_port_valid(uint32_t port)
{
    if(port <= 65535)
        return true;

    return false;
}


//获取本地IP
QString common::Get_LocalIp()
{
    QString hostName=QHostInfo::localHostName();            //本地主机名
    QHostInfo hostInfo=QHostInfo::fromName(hostName); //本机IP地址
    QList<QHostAddress> addList=hostInfo.addresses();      //IP地址列表
    for (int i=0;i<addList.count();i++)
    {
        QHostAddress aHost=addList.at(i); //每一项是一个QHostAddress
        if(QAbstractSocket::IPv4Protocol==aHost.protocol())
        {
            return aHost.toString(); //显示出Ip地址
        }
    }
    return QString("");
}

uint8_t common::qbtarray_to_u8(const QByteArray &ay, uint16_t index)
{
    return (uint8_t)ay[index];
}

uint16_t common::qbtarray_to_u16(const QByteArray &ay, uint16_t index)
{
    return ((uint8_t)ay[index] << 8) + (uint8_t)ay[index +1];
}

uint32_t common::qbtarray_to_u32(const QByteArray &ay, uint16_t index)
{
    return ((uint8_t)ay[index] << 24) +((uint8_t)ay[index+1] << 16) + ((uint8_t)ay[index+2] << 8) + (uint8_t)ay[index+3];
}

QByteArray common::u32_to_qbytearray(uint32_t i)
{
    QByteArray tmp_byarray;
    tmp_byarray.resize(4);

    tmp_byarray[0] = (uint8_t) (i>> 24);
    tmp_byarray[1] = (uint8_t) (i>>16);
    tmp_byarray[2] = (uint8_t) (i>>8);
    tmp_byarray[3] = (uint8_t) i;
    return tmp_byarray;
}

QByteArray common::u16_to_qbytearray(uint16_t i)
{
    QByteArray tmp_byarray;
    tmp_byarray.resize(2);

    tmp_byarray[0] = (uint8_t) (i>> 8);
    tmp_byarray[1] = (uint8_t) i;
    return tmp_byarray;
}

qint64 common::cal_time_interval(QString start_time)
{
    QDateTime tmp_start_time = QDateTime::fromString(start_time,"yyyy-MM-dd hh:mm:ss");
    QDateTime tmp_end_time = QDateTime::currentDateTime();
    qint64 time_interval = 21600; //6小时
    time_interval = tmp_start_time.secsTo(tmp_end_time);
    return time_interval /60;
}

uint16_t common::get_system_yearmon_time()
{
    QDateTime tmp_time = QDateTime::currentDateTime();
    return tmp_time.toString("yyMM").toUInt();
}

QString common::get_system_detail_offset_time(QString date_offset_type, int64_t offset)
{
    QDateTime tmp_time = QDateTime::currentDateTime();
    QDateTime tmp_offset_time;
    //偏移时间类型
    if(date_offset_type == "minute")
    {
        tmp_offset_time = tmp_time.addSecs(offset);
    }
    return tmp_offset_time.toString("yyyy-MM-dd hh:mm:ss");
}

QString common::get_system_detail_time()
{
    QDateTime tmp_time = QDateTime::currentDateTime();
    return tmp_time.toString("yyyy-MM-dd hh:mm:ss");
}



void common::qbytearray_set_value(QByteArray &data, uint32_t start, uint32_t size, uint8_t value)
{
    for (uint32_t i = 0; i < size; ++i) {
        data[i + start] = value;
    }
}

QJsonObject common::qbytearray_to_js(QByteArray data)
{
    QJsonObject root_obj;
    QJsonParseError err_pt;
    QJsonDocument root_doc = QJsonDocument::fromJson(data,&err_pt);
    if(err_pt.error == QJsonParseError::NoError)
    {
        root_obj = root_doc.object();
    }
    return root_obj;
}

QByteArray common::js_to_qbytearray(QJsonObject root_obj)
{
    QJsonDocument body_doc;
    body_doc.setObject(root_obj);

    return body_doc.toJson(QJsonDocument::Compact);
}





