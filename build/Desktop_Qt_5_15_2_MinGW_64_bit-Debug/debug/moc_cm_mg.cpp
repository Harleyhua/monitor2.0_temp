/****************************************************************************
** Meta object code from reading C++ file 'cm_mg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../sys_mg/cm_mg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cm_mg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_cm_mg_t {
    QByteArrayData data[7];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_cm_mg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_cm_mg_t qt_meta_stringdata_cm_mg = {
    {
QT_MOC_LITERAL(0, 0, 5), // "cm_mg"
QT_MOC_LITERAL(1, 6, 13), // "s_send_cs_msg"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 3), // "msg"
QT_MOC_LITERAL(4, 25, 18), // "onm_timer_callback"
QT_MOC_LITERAL(5, 44, 20), // "onm_timer_callback_2"
QT_MOC_LITERAL(6, 65, 13) // "onm_new_timer"

    },
    "cm_mg\0s_send_cs_msg\0\0msg\0onm_timer_callback\0"
    "onm_timer_callback_2\0onm_new_timer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cm_mg[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   37,    2, 0x0a /* Public */,
       5,    0,   38,    2, 0x0a /* Public */,
       6,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void cm_mg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<cm_mg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->s_send_cs_msg((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->onm_timer_callback(); break;
        case 2: _t->onm_timer_callback_2(); break;
        case 3: _t->onm_new_timer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (cm_mg::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&cm_mg::s_send_cs_msg)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject cm_mg::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_cm_mg.data,
    qt_meta_data_cm_mg,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *cm_mg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cm_mg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_cm_mg.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int cm_mg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void cm_mg::s_send_cs_msg(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
