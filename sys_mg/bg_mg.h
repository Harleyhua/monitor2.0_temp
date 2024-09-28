#ifndef BG_MG_H
#define BG_MG_H

#include <QObject>
#include "sys_mg/cm_mg.h"
#include "sys_mg/data_mg.h"
#include "sys_mg/sys_mg.h"
class bg_mg : public QObject
{
    Q_OBJECT
public:
    explicit bg_mg(QObject *parent = nullptr);
    ~bg_mg();
    static bg_mg& ins();

    cm_mg *cm_mg_ins();
    data_mg *data_mg_ins();
    sys_mg *sys_mg_ins();
private:
    cm_mg *m_cm_mg_ins = nullptr;
    data_mg *m_data_mg_ins = nullptr;
    sys_mg *m_sys_mg_ins = nullptr;
signals:

};

#endif // BG_MG_H
