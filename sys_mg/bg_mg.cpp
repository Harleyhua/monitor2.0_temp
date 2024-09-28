#include "bg_mg.h"

bg_mg::bg_mg(QObject *parent)
    : QObject{parent}
{
    m_cm_mg_ins = new cm_mg();
    m_data_mg_ins = new data_mg();
    m_sys_mg_ins = new sys_mg();

    //信号：发送tcp 指令  槽：socket 发送
    connect(m_data_mg_ins,&data_mg::s_send_cs_msg,m_cm_mg_ins->m_socket,&tcp_socket::onm_send_msg);
    //信号：接收到数据  槽：数据缓存到解析类
    connect(m_cm_mg_ins->m_socket,&tcp_socket::s_new_msg,&m_data_mg_ins->m_data_analysis,&cdata_analysis::onm_new_msg);
}

bg_mg::~bg_mg()
{
    delete m_cm_mg_ins;
    delete m_data_mg_ins;
    delete m_sys_mg_ins;
}

bg_mg &bg_mg::ins()
{
    static bg_mg bg(nullptr);
    return bg;
}

cm_mg *bg_mg::cm_mg_ins()
{
    return m_cm_mg_ins;
}

data_mg *bg_mg::data_mg_ins()
{
    return m_data_mg_ins;
}

sys_mg *bg_mg::sys_mg_ins()
{
    return m_sys_mg_ins;
}
