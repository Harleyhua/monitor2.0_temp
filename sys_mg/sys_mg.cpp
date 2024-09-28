#include "sys_mg.h"
#include "sys_mg/bg_mg.h"
sys_mg::sys_mg(QObject *parent)
    : QObject{parent}
{

}

sys_mg::~sys_mg()
{
    m_sys_thread.quit();
    m_sys_thread.wait();

    m_socket_thread.quit();
    m_socket_thread.wait();

    m_data_analysis_thread.quit();
    m_data_analysis_thread.wait();
}

void sys_mg::start()
{
    bg_mg::ins().moveToThread(&m_sys_thread);
    bg_mg::ins().cm_mg_ins()->moveToThread(&m_socket_thread);
    bg_mg::ins().cm_mg_ins()->m_socket->moveToThread(&m_socket_thread);
    bg_mg::ins().data_mg_ins()->moveToThread(&m_data_analysis_thread);
    m_sys_thread.start();
    m_socket_thread.start();
    m_data_analysis_thread.start();
}


