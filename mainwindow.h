#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sys_mg/cm_mg.h"
#include <QTimer>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#include <QDoubleValidator>

class MyDoubleValidator: public QDoubleValidator
{
public:
    MyDoubleValidator(double bottom, double top, int decimals, QObject * parent = 0) :
        QDoubleValidator(bottom, top, decimals, parent)
    {
    }

    QValidator::State validate(QString &s, int &i) const
    {
        if (s.isEmpty() || s == "-") {
            return QValidator::Intermediate;
        }

        QChar decimalPoint = locale().decimalPoint();

        if(s.indexOf(decimalPoint) != -1) {
            int charsAfterPoint = s.length() - s.indexOf(decimalPoint) - 1;

            if (charsAfterPoint > decimals()) {
                return QValidator::Invalid;
            }
        }

        bool ok;
        double d = locale().toDouble(s, &ok);

        if(ok)
        {
            if(d >= bottom() && d <= top())
            {
                return QValidator::Acceptable;
            }
            else if(d < bottom())
            {
                if((((int)bottom())/10) > (((int)d)/10))
                {
                    return QValidator::Acceptable;
                }
                else
                {
                    return QValidator::Invalid;
                }
            }
        }
        return QValidator::Invalid;
    }
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    cm_mg *m_cm_mg;
    tcp_socket *mytcp;
    QThread m_thread;
    QThread m_socket_thread;
    QTimer testTimer;

    QThread m_connect_thread;
signals:
    void s_cm_start();

private slots:
    void on_st_pb_clicked();
    void on_sent_btn_clicked();

public slots:
    void onm_write_inf(QString text);
    void onm_timer_callback();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
