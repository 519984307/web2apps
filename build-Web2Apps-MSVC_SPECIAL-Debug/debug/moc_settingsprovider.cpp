/****************************************************************************
** Meta object code from reading C++ file 'settingsprovider.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Web2Apps/settingsprovider.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingsprovider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_settingsprovider_t {
    QByteArrayData data[10];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_settingsprovider_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_settingsprovider_t qt_meta_stringdata_settingsprovider = {
    {
QT_MOC_LITERAL(0, 0, 16), // "settingsprovider"
QT_MOC_LITERAL(1, 17, 14), // "settingChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 9), // "meChanged"
QT_MOC_LITERAL(4, 43, 10), // "setSetting"
QT_MOC_LITERAL(5, 54, 3), // "key"
QT_MOC_LITERAL(6, 58, 5), // "value"
QT_MOC_LITERAL(7, 64, 9), // "localOnly"
QT_MOC_LITERAL(8, 74, 10), // "getSetting"
QT_MOC_LITERAL(9, 85, 2) // "me"

    },
    "settingsprovider\0settingChanged\0\0"
    "meChanged\0setSetting\0key\0value\0localOnly\0"
    "getSetting\0me"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_settingsprovider[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       1,   58, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    0,   42,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       4,    3,   43,    2, 0x02 /* Public */,
       4,    2,   50,    2, 0x22 /* Public | MethodCloned */,
       8,    1,   55,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QVariant, QMetaType::Bool,    5,    6,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QVariant,    5,    6,
    QMetaType::QVariant, QMetaType::QString,    5,

 // properties: name, type, flags
       9, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       1,

       0        // eod
};

void settingsprovider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        settingsprovider *_t = static_cast<settingsprovider *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->settingChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->meChanged(); break;
        case 2: _t->setSetting((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2])),(*reinterpret_cast< const bool(*)>(_a[3]))); break;
        case 3: _t->setSetting((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariant(*)>(_a[2]))); break;
        case 4: { QVariant _r = _t->getSetting((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (settingsprovider::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&settingsprovider::settingChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (settingsprovider::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&settingsprovider::meChanged)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        Q_ASSERT(staticMetaObject.cast(_o));
        settingsprovider *_t = static_cast<settingsprovider *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->me(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        Q_ASSERT(staticMetaObject.cast(_o));
        settingsprovider *_t = static_cast<settingsprovider *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMe(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject settingsprovider::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_settingsprovider.data,
      qt_meta_data_settingsprovider,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *settingsprovider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *settingsprovider::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_settingsprovider.stringdata0))
        return static_cast<void*>(const_cast< settingsprovider*>(this));
    return QObject::qt_metacast(_clname);
}

int settingsprovider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void settingsprovider::settingChanged(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void settingsprovider::meChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
