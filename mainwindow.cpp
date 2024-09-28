#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "libmodbus/modbus.h"
#include <QTcpSocket>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1200,900);

    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "老化房ID" << "MODBUS采集状态" <<
                                               "服务器通讯状态" << "老化房运行状态" <<"设定温度" << "采集温度"<<
                                               "上报时间");
    //设置最后一栏自适应长度
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    //开启交替行背景色,在设置style为交替颜色时必须开启
    ui->tableWidget->setAlternatingRowColors(true);
    //设置不可编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //关闭默认行号
    ui->tableWidget->verticalHeader()->setHidden(true);
    ui->tableWidget->setSelectionBehavior(QTableWidget::SelectRows);
    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->setColumnWidth(3,150);
    ui->tableWidget->setColumnWidth(4,150);
    ui->tableWidget->setColumnWidth(5,150);
    ui->tableWidget->setColumnWidth(6,350);

    m_cm_mg = new cm_mg(this);
    //让 m_cm_mg 对象在 m_thread 线程中执行，而不是在主线程中执行
    m_cm_mg->moveToThread(&m_thread);
    //m_cm_mg->m_server_socket->moveToThread(&m_thread);

    ui->ip_lb->setVisible(false);
    ui->ip_edt->setVisible(false);
    ui->port_lb->setVisible(false);
    ui->port_edt->setVisible(false);
    ui->lineEdit->setVisible(false);
    ui->st_pb->setVisible(false);
    ui->sent_btn->setVisible(false);

    // ui->ip_lb->setVisible(true);
    // ui->ip_edt->setVisible(true);
    // ui->port_lb->setVisible(true);
    // ui->port_edt->setVisible(true);
    // ui->lineEdit->setVisible(true);
    // ui->st_pb->setVisible(true);

    // ui->ip_edt->setText("192.168.7.237");
    // ui->port_edt->setText("40032");

    m_thread.start();

    // QDoubleValidator * doubleValidator = new QDoubleValidator(40, 80, 1);
    // doubleValidator->setNotation(QDoubleValidator::StandardNotation);
    // ui->lineEdit->setValidator(doubleValidator);

    m_socket_thread.start();
    connect(this,&MainWindow::s_cm_start,m_cm_mg,&cm_mg::onm_new_timer);
    //定时清理 运行状态信息输出控件
    connect(&testTimer,&QTimer::timeout,this,&MainWindow::onm_timer_callback);
    testTimer.start(180000);

    // 发送s_cm_start信号
    emit s_cm_start();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_st_pb_clicked()
{
    if(ui->st_pb->text() == "开始")
    {
        ui->st_pb->text() = "停止";
    }
    else
    {
        ui->st_pb->text() = "开始";
    }
}

void MainWindow::onm_write_inf(QString text)
{
    ui->textBrowser->moveCursor(QTextCursor::Start);
    ui->textBrowser->append(text);
}

void MainWindow::onm_timer_callback()
{
    static uint32_t s60 = 0;
    s60 ++;
    if(s60 >= 2)
    {
        ui->textBrowser->clear();
        s60 = 0;
    }
}

void MainWindow::on_sent_btn_clicked()
{
    // tcpSocket->write(ui->lineEdit->text().toUtf8());
}

